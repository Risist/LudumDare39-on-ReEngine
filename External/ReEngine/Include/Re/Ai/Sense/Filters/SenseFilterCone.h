#pragma once
#include <Re\Ai\Sense\Filters\SenseFilterCircle.h>

namespace Sense
{
	class FilterCone : public FilterCircle
	{
	public:
		FilterCone(float32 radius, Angle width, Vector2D offset = Vector2D(), Angle coneOffset = Angle::zero);
		FilterCone(filtering_t addictionalFiltering, Angle width, float32 radius, Vector2D offset = Vector2D(), Angle coneOffset = Angle::zero);

		virtual bool filter(Game::Actor* actor) override;

		Angle coneOffset, width;
	};
}