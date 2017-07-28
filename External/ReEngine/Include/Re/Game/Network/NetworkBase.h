#pragma once
#include <Re\Common\utility.h>

namespace Game
{
	class Actor;
}


namespace Network
{
	/// Settings
	const unsigned char MAX_PLAYERS = 8;
	const unsigned short SERVER_PORT = 54000;
	const unsigned short MAX_PREFABS = 100;

	enum MessageTypeClient : sf::Uint8
	{
		connectPlayer,
		disconnectPlayer,
		updateOPlayer,
	};

	enum MessageTypeServer : sf::Uint8
	{
		addObject,
		removeObject,
		updateObject,
	};



	/// basic interface for events in clients
	class BaseClient
	{
	public:
		virtual ~BaseClient() {}

		virtual void onStart(Packet& settings) {};

		/// called every frame when actor is alive
		virtual Packet onUpdate(sf::Time dt, Packet& fromServer) {}
		/// called every frame when actor is dead
		virtual Packet onDeath(sf::Time dt, Packet& fromServer) {}

	};

	/// basic interface for events in server
	class BaseServer
	{
	public:
		virtual ~BaseServer() {}

		/// caled when actor is added to actor list. 
		/// In case of components: addictionaly called when adding component to actor already in actors list
		virtual void onStart() {}


		/// called every frame when actor is alive
		/// dt is time elapsed between updates
		virtual void onUpdate(sf::Time dt) {}
		/// called when actor is dead
		/// returns whether or not actor can be safely removed
		virtual bool onDeath(sf::Time dt) { return true; }


		/// physics events
		virtual void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact) { }
		virtual void onCollisionExit(Game::Actor& otherActor, b2Contact& contact) { }
		virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture) { return true; }

	};

	/*
	*	Basic entity placed within game world - client side
	*	Main tasks:
	*		Displaying visuals
	*		Synchronising to received state from server
	*		Sending input data to server
	*/
	class ActorClient : public BaseClient
	{
	public:
		bool isAlive() {
			return true; /// TODO 
		};


	};

	/*
	*	Basic entity placed within game world - server side
	*	Main tasks:
	*		Checking collisions and reacting to them
	*		Sending data to clients about current state
	*		Updating game logic
	*		Geting input from players
	*/
	class ActorServer : public BaseServer
	{
	public:
		bool isAlive() { 
			return true; /// TODO 
		};


		/// called while adding new actor to server
		/// message is send to clients to create specified actor
		/// first data should be 
		virtual void fillClientPrefabData(Packet& dataToSend) {};

	};

	class WorldClient
	{
	public:
		/// functions used for replication
		/// server sends prefab id and addictional initialisation data in package
		typedef function<ActorClient*(Packet&)> ActorPrefab;

		~WorldClient();

		inline void connect();

		void init();
		void run(sf::Time dt);

		/// removes all actors from actor list
		void clear();

		/// adds new prefab function, returns its id
		size_t addNewPrefab(ActorPrefab prefab)
		{
			assert(prefabNoumber < MAX_PREFABS);
			prefabFunctions[++prefabNoumber] = prefab;
			return prefabNoumber;
		}

	private:
		ActorPrefab prefabFunctions[MAX_PREFABS];
		uint16 prefabNoumber;

		void addActor(Packet& packet);

		/// the one actor that can send data to server, player controlled character with its input
		/// when equal to nullptr client has no influence on server
		ActorClient *OwnedCharacter{nullptr};
		std::list<ActorClient*> actorList;

		/// socket which allows to communicate witch server;
		sf::UdpSocket socket;
		sf::IpAddress serverAdress; /// server adress loaded from initialisation file
	};



	class WorldServer
	{
	public:
		~WorldServer();

		inline void connect();

		void init();
		void run(sf::Time dt);

		/// removes all actors
		void clear();

		inline b2World& getPhysics() { return physicalWorld; }
		
		ActorServer *addActor(ActorServer * _new);

	private:
		/// list of actors which should be added to actors list ad end of update cycle
		list<ActorServer*> actorsToAdd;

		/// struct holding data about player
		struct PlayerData
		{

			__forceinline bool isOwned() { return ownedCharacter != nullptr; }

			/// character controlled by player, the only one which can send information to server
			/// if equal to nullptr no player controlls it;
			ActorServer *ownedCharacter{nullptr};
			
			/// adress and port of player, setted up at connection. All updates are sended there
			sf::IpAddress adress;
			unsigned short port;
		};
		PlayerData players[MAX_PLAYERS];

		std::list<ActorServer*> actorList;
		sf::UdpSocket socket;


		b2World physicalWorld;
		/// box2d callbacks
		class ContactFilter : public b2ContactFilter{
		public:
			virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
		} contactFilter;
		class ContactListener : public b2ContactListener{
		public:
			virtual void BeginContact(b2Contact* contact) override;
			virtual void EndContact(b2Contact* contact) override;
		} contactListener;
	};


}