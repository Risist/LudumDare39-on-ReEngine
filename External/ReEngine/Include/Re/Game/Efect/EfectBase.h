#pragma once
#include <Re\Common\utility.h>

namespace Game
{
	class Actor;
}

namespace Efect
{
	/// component-like class for Actors
	class Base
	{
	public:
		Base();
		virtual ~Base(){}


		/// events - similar to those from Actor
		/// here is only dcription of eventually differences or things that are unclear
		/// So for more info look into GameActor.h file

		/// called after owner ptr is set up
		virtual void onInit() {}
		/// called once when actor is added to world list
		/// or when efect is inserted to already added actor
		virtual void onStart() {}
		/// called every frame when actor is alive
		virtual void onUpdate(sf::Time dt) {}
		/// called every frame when actor is dead
		/// returns whether or not can be removed from memory
		virtual bool onDeath(sf::Time dt) {  return true; }

		virtual void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact) { }
		virtual void onCollisionExit(Game::Actor& otherActor, b2Contact& contact) { }
		/// "Liberum veto" all efects have to agree that collision can appear
		virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture) { return true; }


	
	private:
		Game::Actor* owner;
	//protected:
		//int8 _padding[6]; ///< explictly declared padding;

	public:
		/// whether or not the efect is activated
		bool activated;
		bool readyToRemove;

		Game::Actor* getOwner() { assert(owner != nullptr); return owner; }
		const Game::Actor* getOwner() const { assert(owner != nullptr);  return owner; }
		void setOwner(Game::Actor *s) { owner = s; }

	};
}