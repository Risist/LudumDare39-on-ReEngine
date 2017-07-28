#pragma once
#include <Re\Game\Game.h>
#include <Re\Common\Control\ControlMouseDrag.h>

namespace Efect
{
	/// efect that allows to move player forward, backward, strife, and rotate by moving mouse in x axes
	class RotatedMovement : public Base
	{
	public:
		enum UpdateMode
		{
			none,		//< dont update
			toTransform,	//< update by changing transform
			toRigidbody,	//< update by applying forces (warring! rigidbody is required! )
		}
			updateModePosition {toRigidbody},
			updateModeRotation {toRigidbody};

		RotatedMovement(float32 linearSpeed,
			float32 angularSpeed);

		virtual void onUpdate(sf::Time dt) override;

		RotatedMovement* setKeys(string _codeUp,string _codeDown,
			string _codeLeft,string _codeRight)
		{
			codeUp = _codeUp;
			codeDown = _codeDown;
			codeLeft = _codeLeft;
			codeRight = _codeRight;
			return this;
		}
		RotatedMovement* setModes(UpdateMode positionMode, UpdateMode rotationMode)
		{
			updateModePosition = positionMode;
			updateModeRotation = rotationMode;
			return this;
		}
		RotatedMovement* setModes(UpdateMode wholeMode)
		{
			updateModePosition = wholeMode;
			updateModeRotation = wholeMode;
			return this;
		}

		RotatedMovement* setAngularForceMax(float32 s)
		{
			angularForceMax = s * 1000;
			return this;
		}

		float32 linearSpeed;
		float32 angularSpeed, angularForceMax;

		string codeUp{ "up" }, codeDown{ "down" }, codeLeft{ "left" }, codeRight{"right"};

		/// radius in which mouse will be locked onto screan
		/// if is in [0,lockRadius] or [wnd - lockRadius, wnd]
		/// then mouse is swaped in other side
		/// this ensures ability to continued movement of mouse while rotating
		Vector2D lockRadius{5,5};
	protected:
		Control::MouseDrag drag;
	};

}