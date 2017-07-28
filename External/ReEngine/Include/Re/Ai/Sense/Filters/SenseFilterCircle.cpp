#include <Re\Ai\Sense\Filters\SenseFilterCircle.h>
#include <Re\Game\GameActor.h>

namespace Sense
{
	FilterCircle::FilterCircle(float32 _radius, Vector2D _offset)
		: radius(_radius), offset(_offset)
	{
	}
	FilterCircle::FilterCircle(filtering_t addictionalFiltering, float32 _radius, Vector2D _offset)
		: FilterBase(addictionalFiltering), radius(_radius), offset(_offset)
	{
	}
	bool FilterCircle::filter(Game::Actor * actor)
	{
		Vector2D positionOfOwner = offset.getRotated(owner->getRotation()) + offset;
		return (positionOfOwner - actor->getPosition()).getLenghtSq() < radius * radius;
	}
}