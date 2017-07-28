#include <Re\Ai\Sense\Filters\SenseFilterCone.h>
#include <Re\Game\GameActor.h>

namespace Sense
{


	FilterCone::FilterCone(float32 radius, Angle _width, Vector2D offset, Angle _coneOffset)
		: FilterCircle(radius, offset), width(_width), coneOffset(_coneOffset)
	{
	}

	FilterCone::FilterCone(filtering_t addictionalFiltering, Angle _width, float32 radius, Vector2D offset, Angle _coneOffset)
		: FilterCircle(addictionalFiltering, radius, offset), width(_width), coneOffset(_coneOffset)
	{
	}

	bool FilterCone::filter(Game::Actor * actor)
	{
		Vector2D positionOfOwner = offset.getRotated(owner->getRotation()) + offset;
		Vector2D toOwner = positionOfOwner - actor->getPosition();

		Angle differenceAngle = toOwner.angle() - owner->getRotation();
		return toOwner.getLenghtSq() < radius*radius &&  
			differenceAngle > -coneOffset*0.5 &&  differenceAngle < coneOffset*0.5 ;
	}

}