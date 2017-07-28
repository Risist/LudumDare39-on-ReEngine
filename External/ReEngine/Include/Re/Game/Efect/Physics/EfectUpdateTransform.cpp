#include <Re\Game\Efect\Physics\EfectUpdateTransform.h>
#include <Re\Game\GameActor.h>

namespace Efect
{

	UpdateTransform::UpdateTransform(Mode _positionMode, Mode _rotationMode)
		: positionMode(_positionMode), rotationMode(_rotationMode)
	{
	}

	UpdateTransform::UpdateTransform(Mode _wholeMode)
		:positionMode(_wholeMode), rotationMode(_wholeMode)
	{
	}

	void UpdateTransform::onUpdate(sf::Time dt)
	{
		assert(getOwner()->isRigidbodyCreated());

		if (positionMode == toRigidbody)
		{
			getOwner()->setPosition((Vector2D)getOwner()->getRigidbody().GetPosition() * toSfPosition);
		}
		else if (positionMode == toTransform)
		{
			getOwner()->getRigidbody().SetTransform(
				getOwner()->getPosition()* toB2Position,
				getOwner()->getRigidbody().GetAngle()
			);
		}

		if (rotationMode == toRigidbody)
		{
			getOwner()->setRotation(Radian(getOwner()->getRigidbody().GetAngle()).asDegree());
		}
		else if (rotationMode == toTransform)
		{
			getOwner()->getRigidbody().SetTransform(
				getOwner()->getRigidbody().GetPosition(),
				getOwner()->getRotation().asRadian());
		}
	}
}
