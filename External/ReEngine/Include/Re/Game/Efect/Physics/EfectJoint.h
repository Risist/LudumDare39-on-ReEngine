#pragma once
#include <Re\ReEngine.h>

namespace Efect
{

	class RevoluteJoint : public Efect::Base
	{
	public:
		RevoluteJoint(Game::Actor* actorB);
		void onInit() override;
		void onStart() override;

		RevoluteJoint* setAngle(Angle reference, Angle lower, Angle upper)
		{
			def.lowerAngle = lower.asRadian();
			def.upperAngle = upper.asRadian();
			def.referenceAngle = reference.asRadian();
			def.enableLimit = true;
			return this;
		}
		RevoluteJoint* setPoint(const Vector2D& pointA, const Vector2D& pointB)
		{
			def.localAnchorA = pointA*toB2Position;
			def.localAnchorB = pointB*toB2Position;
			return this;
		}
		RevoluteJoint* setMotor(float32 maxMotorTorque = 999999999.f, float32 motorSpeed = 0)
		{
			def.motorSpeed = motorSpeed;
			def.maxMotorTorque = maxMotorTorque;
			return this;
		}
		RevoluteJoint* enableCollision()
		{
			def.collideConnected = true;
			return this;
		}

		b2RevoluteJointDef def;
		b2RevoluteJoint * joint;
	};

}
