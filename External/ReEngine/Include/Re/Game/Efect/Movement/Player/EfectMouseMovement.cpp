#include <Re\Game\Efect\Movement\Player\EfectMouseMovement.h>
#include <Re\Game\Game.h>
#include <Re\Graphics\Camera.h>

extern RenderWindow wnd;

namespace Efect
{
	MouseMovement::MouseMovement(float32 _movementSpeed, RotateToDirection *_efRotDir, float32 _minimalDistance, string _presscode)
		: MovementAim(_movementSpeed, _efRotDir,_minimalDistance), presscode(_presscode)
	{
	}
	MouseMovement::MouseMovement(float32 _movementSpeed, float32 _minimalDistance, string _presscode)
		: MovementAim(_movementSpeed,_minimalDistance), presscode(_presscode)
	{
	}
	void MouseMovement::onUpdate(sf::Time dt)
	{
		assert(getOwner()->isRigidbodyCreated());

		/// change destination
		if (actionMap.isActive(presscode)&& wnd.hasFocus() )
		{
			destination = cam.mapPixelToCoords( sf::Mouse::getPosition(wnd) );
			arrived = false;
		}
		if(!getArrived())
			setDestination(destination);
		
		MovementAim::onUpdate(dt);
	}
	void MouseMovement::reset()
	{
		MovementAim::reset();
		destination = getOwner()->getPosition();
	}
}