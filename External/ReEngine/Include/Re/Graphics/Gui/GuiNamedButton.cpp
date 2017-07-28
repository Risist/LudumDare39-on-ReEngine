#include <Re\Graphics\Gui\GuiNamedButton.h>

namespace Gui
{
	NamedButton::NamedButton(const Vector2f & pos, const Vector2f & halfWh, function<void()> eventOnPress, State stateMouseOn, State statePressed, State stateMouseOut)
		: Button(pos, halfWh, eventOnPress, stateMouseOn, statePressed, stateMouseOut)
	{
	}

	NamedButton::NamedButton(State constantState, const Vector2f & pos, const Vector2f & halfWh, function<void()> eventOnPress)
		:Button(constantState, pos, halfWh, eventOnPress)
	{
	}

	void NamedButton::update(sf::RenderTarget & target, sf::RenderStates states)
	{
		Button::update(target, states);
		text.updatePosActual(getPosActual());
		text.update(target, states);
	}

	void NamedButton::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Button::serialiseF(file, saver);
	}

	void NamedButton::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Button::deserialiseF(file, loader);
		setName(loader.loadRaw("name", "").c_str() );
		setTextColor(Color(
			loader.load("textClR", 255u),
			loader.load("textClG", 255u),
			loader.load("textClB", 255u),
			loader.load("textClA", 255u)
		));
		setTextOutlineColor(Color(
			loader.load("textOutlineClR", 255u),
			loader.load("textOutlineClG", 255u),
			loader.load("textOutlineClB", 255u),
			loader.load("textOutlineClA", 255u)
		));
		setTextOutlineThickness(loader.load("textThickness", 0u));
		setTextSize(loader.load("textSize", 20u));
	}

}