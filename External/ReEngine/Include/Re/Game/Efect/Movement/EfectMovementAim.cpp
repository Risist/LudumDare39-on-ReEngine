#include <Re\Game\Efect\Movement\EfectMovementAim.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	MovementAim::MovementAim(float32 _movementSpeed, RotateToDirection *_efRotDir, float32 _minimalDistance)
		: movementSpeed(_movementSpeed), efRotDir(_efRotDir), arrived(true), minimalDistance(_minimalDistance)
	{
	}
	MovementAim::MovementAim(float32 _movementSpeed, float32 _minimalDistance)
		: movementSpeed(_movementSpeed),
		efRotDir(new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.11f)),
		arrived(true), minimalDistance(_minimalDistance)
	{
	}

	void MovementAim::onInit()
	{
		if (efRotDir)
		{
			getOwner()->addEfect(efRotDir);
		}
	}

	void MovementAim::onUpdate(sf::Time dt)
	{
		/// check if influence is strong enough
		if (storedInfluence.getLenghtSq() < minimalDistance*minimalDistance)
		{
			/// stored influence is too low
			reset();
		}

		/// execute movement
		if (!arrived)
		{
			getOwner()->getRigidbody().ApplyForceToCenter(
				storedInfluence.getNormalised() * movementSpeed*dt.asSeconds() * 1000, true);

			if (efRotDir)
				efRotDir->direction = storedInfluence.angle();
		
			storedInfluence *= influenceFall;
		}

	}

	void MovementAim::setDestinationDirection(const Vector2D & newDest, float32 influenceScale)
	{
		Vector2D v = (newDest - (Vector2D)getOwner()->getRigidbody().GetPosition() * toSfPosition);
		storedInfluence += v.getNormalised()*influenceScale;
		arrived = false;
	}

	void MovementAim::setDestination(const Vector2D& newDest, float32 influenceScale)
	{
		Vector2D v = (newDest - (Vector2D)getOwner()->getRigidbody().GetPosition() * toSfPosition);
		storedInfluence += v*influenceScale;
		arrived = false;
	}


	Vector2D MovementAim::getDestination() const
	{
		return storedInfluence + (Vector2D)getOwner()->getRigidbody().GetPosition();
	}
}