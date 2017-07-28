#include <Re\Graphics\Gui\GuiProgressBar.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	ProgressBar::ProgressBar(
		const Vector2f & _pos, const Vector2f & _halfWh,
		State _background, State _foreground,
		float _initialState)
		:Base(_pos), background(_background), foreground(_foreground),
		progress(_initialState), direction(Direction::left)
	{
		halfWh = _halfWh;
	}


	void ProgressBar::update(RenderTarget & wnd, RenderStates states)
	{
		/// background
		{
			sf::RectangleShape sh;
			sh.setPosition(getPosActual());

			sh.setSize(Vector2f(halfWh.x * 2, halfWh.y * 2));
			sh.setOrigin(halfWh);

			sh.setFillColor(background.cl);
			background.ts.setRectShape(sh);
			wnd.draw(sh, states);
		}
		
		/// foreground
		{
			sf::ConvexShape sh(4);
			sh.setPosition(getPosActual());
			sh.setFillColor(foreground.cl);
			foreground.ts.setConvexShape(sh);
			/*	--		+-
					 A
				-+		++	*/
			if (direction == Direction::right)
			{
				sh.setPoint(0, Vector2D(-halfWh.x, -halfWh.y));
				sh.setPoint(1, Vector2D(-halfWh.x + halfWh.x*2*progress, -halfWh.y));
				sh.setPoint(2, Vector2D(-halfWh.x + halfWh.x*2*progress, halfWh.y));
				sh.setPoint(3, Vector2D(-halfWh.x, halfWh.y));
			}
			else if (direction == Direction::left)
			{
				sh.setPoint(0, Vector2D(halfWh.x - halfWh.x * 2 * progress, -halfWh.y));
				sh.setPoint(1, Vector2D(halfWh.x , -halfWh.y));
				sh.setPoint(2, Vector2D(halfWh.x , halfWh.y));
				sh.setPoint(3, Vector2D(halfWh.x - halfWh.x * 2 * progress, halfWh.y));
			}
			else if (direction == Direction::up)
			{
				sh.setPoint(0, Vector2D(-halfWh.x, -halfWh.y + halfWh.y * 2 * progress));
				sh.setPoint(1, Vector2D(halfWh.x, -halfWh.y + halfWh.y * 2 * progress));
				sh.setPoint(2, Vector2D(halfWh.x, halfWh.y));//
				sh.setPoint(3, Vector2D(-halfWh.x, halfWh.y));//
			}
			else if (direction == Direction::down)
			{
				sh.setPoint(0, Vector2D(-halfWh.x, -halfWh.y)); //
				sh.setPoint(1, Vector2D(halfWh.x, -halfWh.y)); //
				sh.setPoint(2, Vector2D(halfWh.x, -halfWh.y + halfWh.y * 2 * progress));
				sh.setPoint(3, Vector2D(-halfWh.x, -halfWh.y + halfWh.y * 2 * progress));
			}
			wnd.draw(sh, states);
		}
	}

	void ProgressBar::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}
	void ProgressBar::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);
		progress = loader.load("progress", 1.f);

		int ts = loader.load("backTs", (ResId)-1);
		if (ts != -1) background.ts = tsInst[(ResId)ts];

		ts = loader.load("foreTs", (ResId)-1);
		if (ts != -1) foreground.ts = tsInst[(ResId)ts];

		background.cl.r = (sf::Uint8)loader.load("backClR", 255u);
		background.cl.g = (sf::Uint8)loader.load("backClG", 255u);
		background.cl.b = (sf::Uint8)loader.load("backClB", 255u);
		background.cl.a = (sf::Uint8)loader.load("backClA", 255u);

		foreground.cl.r = (sf::Uint8)loader.load("foreClR", 255u);
		foreground.cl.g = (sf::Uint8)loader.load("foreClG", 255u);
		foreground.cl.b = (sf::Uint8)loader.load("foreClB", 255u);
		foreground.cl.a = (sf::Uint8)loader.load("foreClA", 255u);
	
		string dir = loader.load<string>("direction", "left");
		if (dir == "left")
			direction = Direction::left;
		else if (dir == "right")
			direction = Direction::right;
		else if (dir == "up")
			direction = Direction::up;
		else if (dir == "down")
			direction = Direction::down;

	}
}
