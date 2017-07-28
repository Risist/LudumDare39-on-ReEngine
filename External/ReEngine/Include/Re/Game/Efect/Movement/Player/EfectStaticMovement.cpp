#include <Re\Game\Efect\Movement\Player\EfectStaticMovement.h>
#include <Re\Game\Game.h>

namespace Efect
{
	StaticMovement::StaticMovement(float32 _linearSpeed,
		RotateToDirection *_efRotDir)
		: linearSpeed(_linearSpeed), efRotDir(_efRotDir)
	{
		
	}
	StaticMovement::StaticMovement(float32 _linearSpeed)
		: linearSpeed(_linearSpeed), efRotDir(new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.11f))
	{

	}

	void StaticMovement::onInit()
	{
		if (efRotDir)
		{
			getOwner()->addEfect(efRotDir);
		}
	}

	void StaticMovement::onUpdate(sf::Time dt)
	{
		assert(getOwner()->isRigidbodyCreated());
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
			getOwner()->getRigidbody().ApplyForceToCenter(offset*linearSpeed*dt.asSeconds()*1000, true);
			if (efRotDir)
				efRotDir->direction = offset.angle();
		}
	}
	/////////////////////////////////
	//// Joystick
	/////////////////////////////////
	StaticMovementJoystick::StaticMovementJoystick(float32 linearSpeed)
		: StaticMovement(linearSpeed)
	{

	}
	
	StaticMovementJoystick::StaticMovementJoystick(float32 linearSpeed, RotateToDirection *efRotDir)
		: StaticMovement(linearSpeed, efRotDir)
	{

	}

	void StaticMovementJoystick::onUpdate(sf::Time dt)
	{
		assert(getOwner()->isRigidbodyCreated());
		/*Vector2D offset;
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
		}*/


		Vector2D offset;
		offset.x = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
		offset.y = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y);

		//cout << offset.x << ", " << offset.y << "\n";

		if (offset.getLenghtSq() > 1.f )
		{
			offset.normalise();
			getOwner()->getRigidbody().ApplyForceToCenter(offset*linearSpeed*dt.asSeconds() * 1000, true);
			if (efRotDir)
				efRotDir->direction = offset.angle();
		}
		else if (efRotDir)
		{
			offset.x = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Z);
			offset.y = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::R);

			if (offset.getLenghtSq() > 1.f)
				efRotDir->direction = offset.angle();
		}
	}
}