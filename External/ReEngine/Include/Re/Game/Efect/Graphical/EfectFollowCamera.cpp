#include <Re\Game\Efect\Graphical\EfectFollowCamera.h>
#include <Re\Graphics\Camera.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	FollowCamera::FollowCamera(float32 _yOffset, Angle _addictionalRotation, FollowMode _followMode, Vector2D _lerpAlpha)
		:yOffset(_yOffset), addictionalRotation(_addictionalRotation), followMode(_followMode), lerpAlpha(_lerpAlpha)
	{
	}
	FollowCamera::FollowCamera(FollowMode _followMode, float32 _yOffset, Angle _addictionalRotation, Vector2D _lerpAlpha)
		: yOffset(_yOffset), addictionalRotation(_addictionalRotation), followMode(_followMode), lerpAlpha(_lerpAlpha)
	{
	}
	void FollowCamera::onUpdate(sf::Time dt)
	{
		if(getOwner()->isRigidbodyCreated())
		{
			switch (followMode)
			{
			case all:
				cam.follow((Vector2D)getOwner()->getRigidbody().GetPosition()*toSfPosition,
					Radian(getOwner()->getRigidbody().GetAngle()),
					addictionalRotation, yOffset);
				break;
			case positionOnly:
				cam.followPositionOnly((Vector2D)getOwner()->getRigidbody().GetPosition()*toSfPosition,
					Radian(getOwner()->getRigidbody().GetAngle())
					, yOffset);
				break;
			case rotationOnly:
				cam.followRotationOnly(
					Radian(getOwner()->getRigidbody().GetAngle()),
					addictionalRotation);
				break;
			case allSmooth:
				cam.followSmooth((Vector2D)getOwner()->getRigidbody().GetPosition()*toSfPosition,
					Radian(getOwner()->getRigidbody().GetAngle()),
					lerpAlpha, addictionalRotation, yOffset);
				break;
			case positionOnlySmooth:
				cam.followPositionOnlySmooth((Vector2D)getOwner()->getRigidbody().GetPosition()*toSfPosition,
					Radian(getOwner()->getRigidbody().GetAngle()),
					lerpAlpha.x, yOffset);
				break;
			case rotationOnlySmooth:
				cam.followRotationOnlySmooth(
					(Vector2D)getOwner()->getRigidbody().GetPosition()*toSfPosition,
					Radian(getOwner()->getRigidbody().GetAngle()),
					lerpAlpha.y, addictionalRotation);
				break;
			}
		}else
		{
			switch (followMode)
			{
			case all:
				cam.follow((Vector2D)getOwner()->getPosition(),
					getOwner()->getRotation(),
					addictionalRotation, yOffset);
				break;
			case positionOnly:
				cam.followPositionOnly(getOwner()->getPosition(),
					getOwner()->getRotation()
					, yOffset);
				break;
			case rotationOnly:
				cam.followRotationOnly(
					getOwner()->getRotation(),
					addictionalRotation);
				break;
			case allSmooth:
				cam.followSmooth(getOwner()->getPosition(),
					getOwner()->getRotation(),
					lerpAlpha, addictionalRotation, yOffset);
				break;
			case positionOnlySmooth:
				cam.followPositionOnlySmooth(getOwner()->getPosition(),
					getOwner()->getRotation(),
					lerpAlpha.x, yOffset);
				break;
			case rotationOnlySmooth:
				cam.followRotationOnlySmooth(
					getOwner()->getPosition(),
					getOwner()->getRotation(),
					lerpAlpha.y, addictionalRotation);
				break;
			}
		}
	}

}