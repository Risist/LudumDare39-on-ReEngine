#include <Re\Game\Efect\Movement\EfectRotateToDirection.h>
#include <Re\Game\GameActor.h>
#include "EfectRotateToDirection.h"

namespace Efect
{
	RotateToDirection::RotateToDirection(Mode _mode, float32 _smoothAlpha, Angle _angleOffset)
		: mode(_mode), smoothAlpha(_smoothAlpha), angleOffset(_angleOffset)
	{
	}
	void RotateToDirection::onUpdate(sf::Time dt)
	{
		Angle dir = direction + angleOffset;

		switch (mode)
		{
		case Efect::RotateToDirection::instantTransform:
			getOwner()->setRotation(dir.asDegree());
			break;
		case Efect::RotateToDirection::smoothTransform:
		{
			Angle actual = getOwner()->getRotation();
			getOwner()->setRotation(
				(actual + dir.minimalDiffirence(actual) * smoothAlpha*dt.asSeconds()*1000).asDegree()
			);
		}
			break;
		case Efect::RotateToDirection::instantPhysics:
			getOwner()->getRigidbody().SetTransform(
				getOwner()->getRigidbody().GetPosition(), dir.asRadian());
			break;
		case Efect::RotateToDirection::smoothPhysics:
		{
			Angle actual = getOwner()->getRotation();
			getOwner()->getRigidbody().SetTransform(getOwner()->getRigidbody().GetPosition(),
				(actual + dir.minimalDiffirence(actual) * smoothAlpha*dt.asSeconds() * 1000).asRadian()
			);
		}
			break;
		default:
			cerr << "EfectRotateToDirection >> mode type = " << mode << " behaviour is not defined" << endl;
			break;
		}
	}
}