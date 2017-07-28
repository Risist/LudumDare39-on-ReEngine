#include <Re\Game\Efect\Movement\Agent\EfectRandomMovement.h>
#include <Re\Game\GameActor.h>

namespace Efect
{


	RandomMovement::RandomMovement(MovementAim * movement, float32 _priority)
		:MovementAimModificator(_priority, movement)
	{
	}

	void RandomMovement::onUpdate(sf::Time dt)
	{
		assert(movement != nullptr);

		if (clock.getElapsedTime() >= tChangeAim)
		{
			newAim();

			clock.restart();
		}
		movement->setDestination(destination,priority);
	}

	void RandomMovement::newAim()
	{
		assert(movement != nullptr);

		tChangeAim = randRange(tChangeAimMin, tChangeAimMax);
		float32 radius = randRange(radiusMin, radiusMax);
		Angle angle = randRange(Angle::zero, Angle::full );

		Vector2D localPosition = (Vector2D(0, radius).getRotated(angle) + offset);
		destination = getOwner()->getPosition() + localPosition.getRotated(getOwner()->getRotation());
	}

}