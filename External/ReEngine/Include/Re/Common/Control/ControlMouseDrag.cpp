#include <Re\Common\Control\ControlMouseDrag.h>
#include <iostream>

extern RenderWindow wnd;

namespace Control
{
	MouseDrag::MouseDrag()
		:locked(false)
	{
		lockedPoint = (Vector2f)sf::Mouse::getPosition(wnd);
	}

	Vector2f MouseDrag::measure()
	{
		Vector2f r = (Vector2f)Mouse::getPosition(wnd) - lockedPoint;

		lockedPoint = (Vector2f)Mouse::getPosition(wnd);

		return r;
	}
	void MouseDrag::loopMouse(Vector2f offset)
	{
		if (wnd.hasFocus() == false)
			return;
		Vector2f mousePosition = (Vector2f)sf::Mouse::getPosition(wnd);

		if (mousePosition.x < offset.x)
		{
			mousePosition.x = wnd.getSize().x - offset.x - 1;
		}
		else if (mousePosition.x > wnd.getSize().x - offset.x)
		{
			mousePosition.x = offset.x + 1;
		}

		if (mousePosition.y < offset.y)
		{
			mousePosition.y = wnd.getSize().y - offset.y - 1;
		}
		else if (mousePosition.y > wnd.getSize().y - offset.y)
		{
			mousePosition.y = offset.y + 1;
		}

		lockedPoint = mousePosition;
		sf::Mouse::setPosition((Vector2i)mousePosition, wnd);
	}
}