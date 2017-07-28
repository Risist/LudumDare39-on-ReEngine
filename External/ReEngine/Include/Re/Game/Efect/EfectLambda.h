#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <functional>

namespace Efect 
{
	class Lambda : public Base
	{
	public:
		/// typedefs for event functions
		typedef function<void()> onInit_t;
		typedef function<void()> onRestart_t;
		typedef function<void(sf::Time dt)> onUpdate_t;
		typedef function<bool(sf::Time dt)> onDeath_t;
		typedef function<void(Game::Actor&, b2Contact&)> onCollisionEnter_t;
		typedef function<void(Game::Actor&, b2Contact&)> onCollisionExit_t;
		typedef function<bool(b2Fixture*, b2Fixture*)> shouldCollide_t;

	public:
		Lambda(
			const onInit_t& __onStart = defaultOnInit,
			const onRestart_t& __onRestart = defaultOnRestart,
			const onUpdate_t& __onUpdate = defaultOnUpdate,
			const onDeath_t& __onDeath = defaultOnDeath,
			const onCollisionEnter_t& __onCollisionEnter = defaultOnCollisionEnter,
			const onCollisionExit_t& __onCollisionExit = defaultOnCollisionExit,
			const shouldCollide_t& __shouldCollide = defaultShouldCollide);
		
	public:
		/// events - similar to those from Actor
		/// here is only dcription of eventually differences or things that are unclear
		/// So for more info look into GameActor.h file
		
		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;
		virtual bool onDeath(sf::Time dt) override;

		virtual void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact) override;
		virtual void onCollisionExit(Game::Actor& otherActor, b2Contact& contact) override;
		virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture) override;

	public: /// defaults

		static void defaultOnInit();
		static void defaultOnRestart();
		static void defaultOnUpdate(sf::Time dt);
		static bool defaultOnDeath(sf::Time dt);
		static void defaultOnCollisionEnter(Game::Actor& otherActor, b2Contact& contact);
		static void defaultOnCollisionExit(Game::Actor& otherActor, b2Contact& contact);
		static bool defaultShouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture);
		
	public:
		/// there are many functions to set so i allow to do so manually
		onInit_t _onInit;
		onRestart_t _onRestart;
		onUpdate_t _onUpdate;
		onDeath_t _onDeath;

		onCollisionEnter_t _onCollisionEnter;
		onCollisionExit_t _onCollisionExit;
		
		shouldCollide_t _shouldCollide;
	};
}