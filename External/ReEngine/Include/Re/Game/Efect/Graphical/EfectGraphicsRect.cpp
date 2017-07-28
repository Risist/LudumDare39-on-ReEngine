#include <Re\Game\Efect\Graphical\EfectGraphicsRect.h>
#include <Re\Graphics\Camera.h>
#include <Re\Game\GameActor.h>

namespace Efect
{	
	GraphicsRect::GraphicsRect(const Vector2D & wh, Color fillColor, Angle rotation, 
		const Vector2D & offset, UpdateMode _updateMode)
		:updateMode(_updateMode)
	{
		shape.setFillColor(fillColor);
		//shape.setOrigin(wh*0.5 + offset);
		shape.setRotation(rotation.asDegree());
		shape.setPosition(offset);

		shape.setPointCount(4);
		shape.setPoint(0, Vector2D(-wh.x * 0.5f, -wh.y * 0.5f));
		shape.setPoint(1, Vector2D(wh.x * 0.5f, -wh.y * 0.5f));
		shape.setPoint(2, Vector2D(wh.x * 0.5f, wh.y * 0.5f));
		shape.setPoint(3, Vector2D(-wh.x * 0.5f, wh.y * 0.5f));
	
	}
	void GraphicsRect::onUpdate(sf::Time dt)
	{
		//sf::ConvexShape sh = shape;
		getOwner()->updateGraphics(shape);
		//sh.move(shape.getPosition() );
		//sh.rotate(shape.getRotation());
		cam.draw(shape);
		//cout << "rotation of " << getOwner() << " is " << shape.getRotation() << endl;
	}
}