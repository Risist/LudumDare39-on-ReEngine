#include <Re\Game\Efect\Movement\Player\EfectRotatedMovement.h>
#include <Re\Graphics\Graphics.h>

namespace Efect
{


	RotatedMovement::RotatedMovement(float32 _linearSpeed, float32 _angularSpeed)
		: linearSpeed(_linearSpeed), angularSpeed(_angularSpeed), angularForceMax(99999999999999999.f)
	{
		wnd.setMouseCursorGrabbed(true);
	}

	void RotatedMovement::onUpdate(sf::Time dt)
	{
		Vector2D offset;
		bool moved = false;

		if (actionMap.isActive(codeUp))
		{
			--offset.y;
			moved = true;
		}
		if (actionMap.isActive(codeDown))
		{
			++offset.y;
			moved = true;
		}
		if (actionMap.isActive(codeLeft))
		{
			--offset.x;
			moved = true;
		}
		if (actionMap.isActive(codeRight))
		{
			++offset.x;
			moved = true;
		}

		if (moved)
		{
			offset.normalise();

			if (updateModePosition == toRigidbody)
			{
				assert(getOwner()->isRigidbodyCreated());
				getOwner()->getRigidbody().ApplyForceToCenter(
					getOwner()->getRigidbody().GetWorldVector(

						offset* linearSpeed*dt.asSeconds() * 1000.f
					), false);
			}
			else if(updateModePosition == toTransform)
			{
				offset.rotate(getOwner()->getRotation());
				getOwner()->move(offset * linearSpeed * dt.asSeconds() * 1000);
			}
		}

		float dragValue = clamp(drag.measure().x * angularSpeed*dt.asSeconds() * 1000, -angularForceMax, angularForceMax);

		if (updateModeRotation == toRigidbody)
		{
			assert(getOwner()->isRigidbodyCreated());
			getOwner()->getRigidbody().ApplyTorque(Degree(dragValue).asRadian(), true);
		}
		else if (updateModeRotation == toTransform)
		{
			getOwner()->rotate(dragValue);
		}
		
		drag.loopMouse(lockRadius);
	}
}