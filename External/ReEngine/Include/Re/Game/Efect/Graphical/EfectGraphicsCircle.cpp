#include <Re\Game\Efect\Graphical\EfectGraphicsCircle.h>
#include <Re\Graphics\Camera.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	GraphicsCircle::GraphicsCircle(Color fillColor, float32 radius, const Vector2D & offset, UpdateMode _updateMode)
		:updateMode(_updateMode)
	{
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.setFillColor(fillColor);
		shape.setPosition(offset.x, offset.y);
	}
	void GraphicsCircle::onUpdate(sf::Time dt)
	{
		sf::CircleShape sh = shape;

		if(updateMode == toTransform)
			getOwner()->updateGraphics(sh);

		cam.draw(sh);
	}
}