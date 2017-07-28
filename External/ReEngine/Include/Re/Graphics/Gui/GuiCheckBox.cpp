#include <Re\Graphics\Gui\GuiCheckBox.h>

namespace Gui
{

	CheckBox::CheckBox(
		const Vector2f & pos, const Vector2f & halfWh,
		function<void()> eventOnPress,
		State stateMouseOn,
		State statePressed,
		State stateMouseOut,
		bool initialState)
		:Button(pos,halfWh,eventOnPress,stateMouseOn,statePressed,stateMouseOut),
		b(initialState), canBeActivatedAgain(true)
	{
	}

	CheckBox::CheckBox(
		State constantState,
		const Vector2f & pos,
		const Vector2f & halfWh,
		function<void()> eventOnPress,
		bool initialState)
		: Button(pos, halfWh, eventOnPress, constantState, constantState, constantState),
		b(initialState), canBeActivatedAgain(true)
	{
	}


	void Gui::CheckBox::update(RenderTarget & wnd, RenderStates states)
	{
		sf::ConvexShape sh(4);
		sh.setPosition(getPosActual());

		sh.setPoint(0, Vector2D(-halfWh.x, -halfWh.y));
		sh.setPoint(1, Vector2D(halfWh.x, -halfWh.y));
		sh.setPoint(2, Vector2D(halfWh.x, halfWh.y));
		sh.setPoint(3, Vector2D(-halfWh.x, halfWh.y));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOnWindow() == false)
			canBeActivatedAgain = false;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
			canBeActivatedAgain = true;

		if (isMouseOnWindow())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (canBeActivatedAgain)
				{
					if (eventOnPress)
						eventOnPress();
					canBeActivatedAgain = false;
					b = !b;
				}
			}
			
		}

		if (b)
		{
			sh.setFillColor(statePressed.cl);
			statePressed.ts.setConvexShape(sh);
		}
		else
		{
			sh.setFillColor(stateMouseOut.cl);
			stateMouseOut.ts.setConvexShape(sh);
		}

		wnd.draw(sh, states);
	}


	void Gui::CheckBox::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Button::serialiseF(file, saver);
		saver.save("initialState", b);
	}
	void Gui::CheckBox::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Button::deserialiseF(file, loader);
		b = loader.load("initialState", false);
	}



}