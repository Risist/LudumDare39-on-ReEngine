#pragma once

#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{

	class ColliderCircle : public Base
	{
	public:
		ColliderCircle(float32 radius, float32 density = 1, Vector2D offset = Vector2D(),
			bool isSensor = false, float32 restitution = 0.3, float32 friction = 0.3);
		void onInit() override;

		b2CircleShape shapeDef;
		b2FixtureDef fixtureDef;
		b2Fixture* fixture{nullptr};
	};

	class ColliderBox : public Base
	{
	public:
		/// wh - width and height
		ColliderBox(Vector2D wh, float32 density = 1,
			bool isSensor = false, float32 restitution = 0.3, float32 friction = 0.3);
		ColliderBox(Vector2D wh, Angle angle, float32 density = 1, Vector2D offset = Vector2D(),
			bool isSensor = false, float32 restitution = 0.3, float32 friction = 0.3);

		void onInit() override;


		b2PolygonShape shapeDef;
		b2FixtureDef fixtureDef;
		b2Fixture* fixture{nullptr};
	};
}