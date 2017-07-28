#pragma once
#include <Re\Ai\Sense\SenseFilterBase.h>

namespace Sense
{
	class FilterCircle : public FilterBase
	{
	public:
		FilterCircle(float32 radius, Vector2D offset = Vector2D() );
		FilterCircle(filtering_t addictionalFiltering, float32 radius, Vector2D offset = Vector2D() );
		virtual bool filter(Game::Actor* actor) override;

		float32 radius;
		Vector2D offset;
	};
}