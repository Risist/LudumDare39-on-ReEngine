#pragma once
#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{
	class GraphicsCircle : public Base
	{
	public:
		enum UpdateMode
		{
			none,
			toTransform
		}updateMode{ toTransform };

		GraphicsCircle( Color fillColor = Color::White, float32 radius = 100, const Vector2D& offset = Vector2D(), UpdateMode updateMode = toTransform);

		virtual void onUpdate(sf::Time dt) override;


		/// display data
		sf::CircleShape shape;

	};
}