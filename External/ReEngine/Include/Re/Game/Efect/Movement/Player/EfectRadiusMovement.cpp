#include <Re\Game\Efect\Movement\Player\EfectRadiusMovement.h>
#include <Re\Game\GameActor.h>
#include <Re\Graphics\Camera.h>
extern RenderWindow wnd;

namespace Efect
{
	RadiusMovement::RadiusMovement(
		float32 _movementSpeed,
		RotateToDirection *_efRotDir,
		float32 _rotationRadius, float32 _movementRadius, float32 _movementRadiusMax)
		: movementSpeed(_movementSpeed), efRotDir(_efRotDir),
			rotationRadius(_rotationRadius), movementRadius(_movementRadius)
		, movementRadiusMax(_movementRadiusMax)
	{
	}
	RadiusMovement::RadiusMovement(
		float32 _movementSpeed,
		float32 _rotationRadius, float32 _movementRadius, float32 _movementRadiusMax)
		: movementSpeed(_movementSpeed), 
		efRotDir(new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.11f)),
		rotationRadius(_rotationRadius), movementRadius(_movementRadius)
		, movementRadiusMax(_movementRadiusMax)
	{
	}

	void RadiusMovement::onInit()
	{
		assert(getOwner()->isRigidbodyCreated());
		if (efRotDir)
		{
			getOwner()->addEfect(efRotDir);
		}
		sf::Mouse::setPosition((Vector2D)wnd.getSize()*0.5f, wnd);
	}
	void RadiusMovement::onUpdate(sf::Time dt)
	{
		assert(getOwner()->isRigidbodyCreated());

		if (wnd.hasFocus() == false)
		{
			return;
			lastSpeedModificator = 0;
		}

		Vector2D toMouse = cam.mapPixelToCoords(
			(Vector2D)sf::Mouse::getPosition(wnd) - (Vector2D)getOwner()->getRigidbody().GetPosition()*toSfPosition
			);
		float32 toMouseRadiusSq = toMouse.getLenghtSq();

		if (toMouseRadiusSq > rotationRadius*rotationRadius)
		{
			if (efRotDir)
				efRotDir->direction = toMouse.angle();

			if (toMouseRadiusSq > movementRadius*movementRadius)
			{
				float32 toMouseRadius = sqrt(toMouseRadiusSq);
				/// normalize
				toMouse /= toMouseRadius;

				toMouseRadius =	clamp(toMouseRadius, movementRadius, movementRadiusMax);
				lastSpeedModificator = (toMouseRadius - movementRadius) / (movementRadiusMax - movementRadius);
				

				getOwner()->getRigidbody().ApplyForceToCenter(toMouse *(lastSpeedModificator* movementSpeed*dt.asSeconds() * 1000), true);
			}
			else
			{
				lastSpeedModificator = 0;
			}
		}
	}
}