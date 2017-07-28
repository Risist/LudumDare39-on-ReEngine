#pragma once
#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{
	class GraphicsRect : public Base
	{
	public:
		enum UpdateMode
		{
			none,
			toTransform
		}updateMode{ toTransform };

		GraphicsRect(const Vector2D& wh = Vector2D(), Color fillColor = Color::White, Angle rotation = Angle(),
			const Vector2D& offset = Vector2D(), UpdateMode updateMode = toTransform);

		virtual void onUpdate(sf::Time dt) override;


		/// display data
		sf::ConvexShape shape;

	};
}