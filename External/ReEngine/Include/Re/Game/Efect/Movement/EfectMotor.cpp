#include <Re\Game\Efect\Movement\EfectMotor.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	Motor::Motor(float32 _movementSpeed, Angle _angleOffset)
		: movementSpeed(_movementSpeed), angleOffset(_angleOffset)
	{
	}

	void Motor::onUpdate(sf::Time dt)
	{
		if (getOwner()->isRigidbodyCreated())
		{
			getOwner()->getRigidbody().ApplyForceToCenter(
				Vector2D(0, -movementSpeed*dt.asSeconds() * 1000).getRotated(
					getOwner()->getRotation() + angleOffset
				), true
			);
		}
		else
		{
			getOwner()->move(
				Vector2D(0, -movementSpeed*dt.asSeconds() * 1000).getRotated(
					getOwner()->getRotation() + angleOffset )
			);
		}
	}
}