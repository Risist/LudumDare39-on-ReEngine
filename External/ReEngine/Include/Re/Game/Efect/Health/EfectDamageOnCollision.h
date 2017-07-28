#pragma once
#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{

	class DamageOnCollision : public Base
	{
	public:
		DamageOnCollision(float32 damage);
		DamageOnCollision(float32 damage, function<bool(Game::Actor& other, b2Contact& contact)> allowdedToDeal);

		void onUpdate(sf::Time dt) override;

		void onCollisionEnter(Game::Actor& other, b2Contact& contact) override;
		void onCollisionExit(Game::Actor& other, b2Contact& contact) override;

		enum Mode
		{
			enter,
			stay,
			exit,
		}mode{enter};

		DamageOnCollision* setMode(Mode newMode)
		{
			mode = newMode;
			return this;
		}

		function<bool(Game::Actor& other, b2Contact& contact)> allowdedToDeal{ [](Game::Actor&, b2Contact&) {return true; } };
		float32 damage;

	private:
		struct Event
		{
			Game::Actor* other;
			b2Contact* contact;
		};
		list<Event> updateEvents;
	};

}