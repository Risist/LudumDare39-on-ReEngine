#pragma once
#include <Re\Game\Efect\Movement\EfectRotateToDirection.h>

namespace Efect
{
	/// efect that allows to move player in x and y axes without any rotation
	/// @Warring:  Rigidbody must be created before a first update of the component!
	class StaticMovement : public Base
	{
	public:
		StaticMovement(float32 linearSpeed);
		StaticMovement(float32 linearSpeed,
			RotateToDirection *efRotDir
		);

		virtual void onInit() override;
		virtual void onUpdate(sf::Time st) override;

		StaticMovement* setKeys(const string& up, const string& down, const string& left, const string& right)
		{
			codeUp = up;
			codeDown = down;
			codeLeft = left;
			codeRight = right;
			return this;
		}

		float32 linearSpeed;
		string codeUp{ "up" };
		string codeDown{ "down" };
		string codeLeft{ "left" };
		string codeRight{ "right" };

		/// pointner to efect which will change direction of owner
		/// nullptr disables the this feature
		RotateToDirection *efRotDir{nullptr};
	};

	class StaticMovementJoystick : public StaticMovement
	{
	public:
		StaticMovementJoystick(float32 linearSpeed);
		StaticMovementJoystick(float32 linearSpeed,
			RotateToDirection *efRotDir
		);

		void onUpdate(sf::Time dt) override;


		int joystickId{0};
	};
}