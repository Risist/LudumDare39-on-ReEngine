#include <Re\Game\Efect\EfectLambda.h>


namespace Efect
{



	Lambda::Lambda(
		const onInit_t & __onInit,
		const onRestart_t & __onRestart,
		const onUpdate_t & __onUpdate,
		const onDeath_t & __onDeath,
		const onCollisionEnter_t & __onCollisionEnter,
		const onCollisionExit_t & __onCollisionExit,
		const shouldCollide_t & __shouldCollide) :
			_onInit(__onInit),
			_onRestart(__onRestart),
			_onUpdate(__onUpdate),
			_onDeath(__onDeath),
			_onCollisionEnter(__onCollisionEnter),
			_onCollisionExit(__onCollisionExit),
			_shouldCollide(__shouldCollide)
	{
	}

	void Lambda::onInit()
	{
		_onInit();
	}

	void Lambda::onUpdate(sf::Time dt)
	{
		_onUpdate(dt);
	}

	bool Lambda::onDeath(sf::Time dt)
	{
		return _onDeath(dt);
	}

	void Lambda::onCollisionEnter(Game::Actor & otherActor, b2Contact & contact)
	{
		_onCollisionEnter(otherActor, contact);
	}

	void Lambda::onCollisionExit(Game::Actor & otherActor, b2Contact & contact)
	{
		_onCollisionExit(otherActor, contact);
	}

	bool Lambda::shouldCollide(b2Fixture * myFixture, b2Fixture * otherFixture)
	{
		return _shouldCollide(myFixture, otherFixture);
	}


	/// defaults 

	void Lambda::defaultOnInit()
	{
	}

	void Lambda::defaultOnRestart()
	{
	}

	void Lambda::defaultOnUpdate(sf::Time dt)
	{
	}

	bool Lambda::defaultOnDeath(sf::Time dt)
	{
		return true;
	}

	void Lambda::defaultOnCollisionEnter(Game::Actor & otherActor, b2Contact & contact)
	{
	}

	void Lambda::defaultOnCollisionExit(Game::Actor & otherActor, b2Contact & contact)
	{
	}

	bool Lambda::defaultShouldCollide(b2Fixture * myFixture, b2Fixture * otherFixture)
	{
		return true;
	}
}