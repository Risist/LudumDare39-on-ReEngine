#include <Re\Game\Efect\Health\EfectDamageOnCollision.h>
#include <Re\Game\GameActor.h>
#include <Re\Game\Efect\Health\EfectHealth.h>

namespace Efect
{
	DamageOnCollision::DamageOnCollision(float32 _damage)
		: damage(_damage)
	{
	}
	DamageOnCollision::DamageOnCollision(float32 _damage, function<bool(Game::Actor&other, b2Contact&contact)> _allowdedToDeal)
		:damage(_damage), allowdedToDeal(_allowdedToDeal)
	{
	}

	void DamageOnCollision::onUpdate(sf::Time dt)
	{
		if (mode == stay)
		{
			for(auto it : updateEvents)
			{
				auto dmgEffect = it.other->getEfect<Health>();
				if (dmgEffect)
				{
					dmgEffect->damage(
						/// dmg measure per one secound
						damage*dt.asSeconds()*1000.f, getOwner());
				}
			}
		}
	}


	void DamageOnCollision::onCollisionEnter(Game::Actor & other, b2Contact & contact)
	{
		if (mode == enter)
		{
			if (allowdedToDeal(other, contact))
			{
				auto dmgEffect = other.getEfect<Health>();
				if (dmgEffect)
				{
					dmgEffect->damage(damage, getOwner());
				}
			}
		}
		else if (mode == stay)
		{
			if (allowdedToDeal(other, contact))
			{
				Event _event;
				_event.other = &other;
				_event.contact = &contact;
				updateEvents.push_back(_event);
			}
		}
	}

	void DamageOnCollision::onCollisionExit(Game::Actor & other, b2Contact & contact)
	{
		if (mode == exit)
		{
			if (allowdedToDeal(other, contact))
			{
				auto dmgEffect = other.getEfect<Health>();
				if (dmgEffect)
				{
					dmgEffect->damage(damage, getOwner());
				}
			}
		}
		else if(mode == stay)
		{
			for (auto it = updateEvents.begin(); it != updateEvents.end(); ++it)
				if (it->other == &other)
					updateEvents.erase(it);
		}
	}

}