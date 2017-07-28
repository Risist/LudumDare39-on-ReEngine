#pragma once

#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{
	/// efect which causes that camera will follow owner of this efect
	/// 
	class FollowCamera : public Base
	{
	public:
		enum FollowMode
		{
			all, /// updates camera's pos & rotation
			positionOnly, /// updates camera's pos only
			rotationOnly, /// updates camera's rotation only
			allSmooth, /// updates camera's pos & rotation with interpolation
			positionOnlySmooth, /// updates camera's pos only with interpolation
			rotationOnlySmooth, /// updates camera's pos only with interpolation
		} followMode;
		FollowCamera(float32 yOffset = 0, Angle addictionalRotation = Angle(), 
			FollowMode followMode = positionOnly, Vector2D lerpAlpha = Vector2D(1,1));
		FollowCamera(FollowMode followMode, float32 yOffset = 0, Angle addictionalRotation = Angle(),
			 Vector2D lerpAlpha = Vector2D(1,1));


		void onUpdate(sf::Time dt) override;

		FollowCamera* setAddictionalRotation(Angle add)
		{
			addictionalRotation = add;
			return this;
		}
		FollowCamera* setLerpPosition(float32 s)
		{
			lerpAlpha.x = s;
			return this;
		}
		FollowCamera* setLerpRotation(float32 s)
		{
			lerpAlpha.y = s;
			return this;
		}
		FollowCamera* setLerp(float32 sPosition, float32 sRotation)
		{
			lerpAlpha.x = sPosition;
			lerpAlpha.y = sRotation;
			return this;
		}
		FollowCamera* setYOffset(float32 s)
		{
			yOffset = s;
			return this;
		}
		FollowCamera* setMode(FollowMode s)
		{
			followMode = s;
			return this;
		}

		Angle addictionalRotation;
		float32 yOffset;
		Vector2D lerpAlpha;
	};

}