#include <Re\Game\Efect\MultiEfect.h>

namespace Efect
{
	void Multi::onInit()
	{
	}
	void Multi::onStart()
	{
		for (auto &it : efects)
			it->onStart();
	}
	void Multi::onUpdate(sf::Time dt)
	{
		for (auto it = efects.begin(); it != efects.end(); )
			if ((*it)->readyToRemove)
				efects.erase(it++);
			else
				++it;

		for (auto &it : efects)
			if (it->activated)
				it->onUpdate(dt);
	}
	bool Multi::onDeath(sf::Time dt)
	{
		bool r = true;
		for (auto &it : efects)
			if (it->activated)
				r = r && it->onDeath(dt);
		return r;
	}
	void Multi::onCollisionEnter(Game::Actor & otherActor, b2Contact & contact)
	{
		for (auto &it : efects)
			if (it->activated)
				it->onCollisionEnter(otherActor, contact);
	}
	void Multi::onCollisionExit(Game::Actor & otherActor, b2Contact & contact)
	{
		for (auto &it : efects)
			if (it->activated)
				it->onCollisionExit(otherActor, contact);
	}
	bool Multi::shouldCollide(b2Fixture * myFixture, b2Fixture * otherFixture)
	{
		bool r = true;
		for (auto &it : efects)
			if (it->activated)
				r = r && it->shouldCollide(myFixture, otherFixture);
		return r;
	}
}

