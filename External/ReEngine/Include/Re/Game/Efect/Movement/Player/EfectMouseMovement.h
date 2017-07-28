#pragma once
#include <Re\Game\Efect\Movement\EfectMovementAim.h>

namespace Efect
{
	/// specialized version of MovementAim for player
	/// uppon activating presscode action from actionMap 
	/// destination is updated to mouse pos within game world
	class MouseMovement: public MovementAim
	{
	public:
		MouseMovement(float32 movementSpeed,
			float32 minimalDistance = 50,
			string presscode = "fire1");
		MouseMovement(float32 movementSpeed,
			RotateToDirection *efRotDir,
			float32 minimalDistance = 50,
			string presscode = "fire1");

		void onUpdate(sf::Time dt) override;

		void reset();
		

		/// code from "actionMap" which sets decides when the character will change its destination
		string presscode;
	private:
		Vector2D destination;
		//bool atMove{ false };
	};

}