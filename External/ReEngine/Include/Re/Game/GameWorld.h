#pragma once
#include <Re\Common\utility.h>
#include <Re\Game\GameActor.h>
#include <Re\Game\Actor\GameLayer.h>

namespace Game
{
	/// calback class to invoke shoud collide event 
	class ContactFilter : public b2ContactFilter
	{ public:
		virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
	};

	/// Callback class to invoke collision events
	class ContactListener : public b2ContactListener
	{ public:
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class World
	{
	public:
		World();
		~World();

		/// removes every actor and physics entity from the world
		void clear();
		

		/// call the event every frame
		/// for now lets say the time is almost constant - but it may change in future versions so be careful
		void onUpdate(sf::Time dt);

		/// acquire a new actor into actors list
		/// layer specify order of running functions. if equal nullptr adds to actorList
		template<class Act >
		Act* addActor(Act *_new, Layer* layer = nullptr);
		

		/// box2d dpisplayDebugData didn't work so it is a work around
		/// displays all physical objects onto screan
		void debugDisplayPhysics(Color clNotColliding, Color clColliding);

		/// 
		b2World physicalWorld;

		list<Actor*>& getActorList()
		{
			return actorList;
		}

	private:
		//friend ContactListener;
		ContactListener contactListener;
		ContactFilter contactFilter;
		
		/// list of actors placed in world
		list<Actor*> actorList;
		
		/// separate lists to not break iterators in main loop
		list<Actor*> actorToAdd;
		list<Actor*> actorToRemove;

		friend Actor;
	};
	extern World world;

	template<class Act>
	Act * World::addActor(Act * _new, Layer * layer)
	{
		if (_new == nullptr)
		{
			cerr << "World::addActor _new = nullptr" << endl;
			return nullptr;
		}
		if (layer)
			layer->addActor(_new);
		else
		{
			actorToAdd.push_back(_new);

			_new->onInit();
		}

		return _new;
	}
}