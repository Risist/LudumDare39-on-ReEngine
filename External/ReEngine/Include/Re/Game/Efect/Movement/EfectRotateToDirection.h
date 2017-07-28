#pragma once
#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{

	/// utility efect (used by other efect)
	/// which rotates owner to given angle
	/// another efect should set up RotateToDirection::direction
	// field every change of desired direction of owner
	class RotateToDirection : public Base
	{
	public:
		enum Mode
		{
			instantTransform, /// instant change when no rigidbody applied
			smoothTransform, /// smooth change (lerp) when no rigidbody applied
			instantPhysics,  /// instant change when rigidbody is applied
			smoothPhysics, /// smooth change (lerp) when rigidbody is applied
		}mode;
		RotateToDirection(Mode mode = instantPhysics, float32 smoothAlpha = 1, Angle angleOffset = Angle() );

		void onUpdate(sf::Time dt) override;

		Angle direction, angleOffset;
		float32 smoothAlpha;
	};

}