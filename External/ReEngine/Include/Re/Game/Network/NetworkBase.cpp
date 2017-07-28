#include <Re\Game\Network\NetworkBase.h>

namespace Network
{



	/********************************/
	/// WorldClient
	/********************************/

	WorldClient::~WorldClient()
	{
		clear();
	}

	inline void WorldClient::connect()
	{
		/// socket initialisation
		socket.bind(sf::Socket::AnyPort);
		socket.setBlocking(false);
	}

	void WorldClient::init()
	{
		connect();
	}

	void WorldClient::run(sf::Time dt)
	{
		/// operate requests from server
		Packet receiveMessage;
		sf::IpAddress remoteAdress;
		unsigned short remotePort;
		while( socket.receive(receiveMessage, remoteAdress, remotePort) == sf::Socket::Done)
		{
			sf::Uint8 messageType;
			receiveMessage >> messageType;

			switch (messageType)
			{
			case MessageTypeServer::addObject:
				addActor(receiveMessage);
				break;
			case MessageTypeServer::removeObject:
				/// TODO
				break;
			case MessageTypeServer::updateObject:
				/// TODO
				break;
			}
		}


		/// update game
		for (auto it = actorList.begin(); it != actorList.end(); ++it)
			if ((*it)->isAlive())
			{
				(*it)->onUpdate(dt, Packet());
			
			}
			else if((*it)->onDeath(dt, Packet() ) )
			{

			}
	}

	void WorldClient::clear()
	{
		for (auto it : actorList)
			if (it)
				delete it;
		actorList.clear();
	}

	void WorldClient::addActor(Packet & packet)
	{
		uint16 prefabId;
		packet >> prefabId;
		assert(prefabId < prefabNoumber);

		ActorClient* actor = prefabFunctions[prefabId](packet);
		assert(actor);
		
		actorList.push_back(actor);
	}

	/********************************/
	/// WorldServer
	/********************************/

	WorldServer::~WorldServer()
	{
		clear();
	}

	inline void WorldServer::connect()
	{
		/// socket initialisation
		socket.bind(SERVER_PORT);
		socket.setBlocking(false);
	}

	void WorldServer::init()
	{
		connect();

		// contact listeners
		physicalWorld.SetContactListener(&contactListener);
		physicalWorld.SetContactFilter(&contactFilter);
	}

	void WorldServer::run(sf::Time dt)
	{


		/// fixed update (?)
		physicalWorld.Step(1.f / 60.f, velocityIterations, positionIterations);


		for (auto it : actorsToAdd)
		{
			/// add to servers actorList
			actorList.push_back(it);
			it->onStart();
			
			/// prepare packet with data about new actor
			sf::Packet creationPacket;

			creationPacket << MessageTypeServer::addObject;
			it->fillClientPrefabData(creationPacket);

			/// send request to all players;
			for(PlayerData* it = players; it != &players[MAX_PLAYERS]; ++it)
				if (it->ownedCharacter)
					socket.send(creationPacket, it->adress, it->port);

		}
		actorsToAdd.clear();

		/// actors are removed after full update cycle to not break some dependences inside
		static vector<ActorServer*> actorsToRemove;

		/// iterate through all actors
		for (auto it = actorList.begin(); it != actorList.end();)
		{
			auto actorIt = *it;

			if (actorIt->isAlive())
			{
				actorIt->onUpdate(dt);
				++it;
			}
			else if (actorIt->onDeath(dt))
			{
				actorsToRemove.push_back(actorIt);
				actorList.erase(it++);
			}
		}

		for (auto it : actorsToRemove)
			delete it;
		actorsToRemove.clear();

	}

	void WorldServer::clear()
	{
		for (auto it : actorList)
			if(it)
				delete it;
		actorList.clear();
	}

	ActorServer * WorldServer::addActor(ActorServer * _new)
	{
		actorsToAdd.push_back(_new);
		return _new;
	}

}