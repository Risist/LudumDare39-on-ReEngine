#include <Re\Game\Efect\Health\EfectHealth.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	Health::Health(float32 maxHealth, float32 percentInitialHealth)
		: max(maxHealth), actual(maxHealth*percentInitialHealth),inverseDefence(1)
	{
	}

	void Health::onUpdate(sf::Time dt)
	{
		if (actual <= 0)
			getOwner()->setAlive(false);

		actual += regeneration;
		regeneration *= regenerationDamping;
	}

	void Health::damage(float32 amount, Game::Actor* causer)
	{
		regeneration -= amount*inverseDefence;
		if (damageReaction)
			damageReaction(-amount, causer);
	}

	void Health::heal(float32 amount, Game::Actor* causer)
	{
		regeneration += amount*inverseDefence;
		if (damageReaction)
			damageReaction(amount, causer);
	}

}