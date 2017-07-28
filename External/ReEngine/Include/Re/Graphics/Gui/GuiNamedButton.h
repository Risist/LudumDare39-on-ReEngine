#pragma once
#include <Re\Graphics\Gui\GuiButton.h>
#include <Re\Graphics\Gui\GuiText.h>

namespace Gui
{
	class NamedButton : public Button
	{
		virtual std::string getClassName() const override { return "NamedButton"; }
	public:
		NamedButton(const Vector2f& pos = Vector2f(), const Vector2f& halfWh = Vector2f(),
			function<void()> eventOnPress = []() {},
			State stateMouseOn = State(),
			State statePressed = State(),
			State stateMouseOut = State()
		);
		NamedButton( State constantState, const Vector2f& pos, const Vector2f& halfWh,
			function<void()> eventOnPress = []() {}
		);
		NamedButton(const string& path) { deserialise(path); }

		virtual void update(sf::RenderTarget& target, sf::RenderStates states) override;

		NamedButton* setState(const State& s)
		{
			stateMouseOn = stateMouseOut = statePressed = s;
			return this;
		}
		NamedButton* setStateMouse(const State& s)
		{
			stateMouseOn = stateMouseOut = s;
			return this;
		}
		NamedButton* setStateMouseOn(const State& s)
		{
			stateMouseOn = s;
			return this;
		}
		NamedButton* setStateMouseOut(const State& s)
		{
			stateMouseOut = s;
			return this;
		}
		NamedButton* setStatePressed(const State& s)
		{
			statePressed = s;
			return this;
		}
		NamedButton* setEvent(function<void()> ev)
		{
			eventOnPress = ev;
			return this;
		}
		NamedButton* setPos(const sf::Vector2f& _new)
		{
			return (NamedButton*)Base::setPos(_new);
		}
		NamedButton* setHalfWh(const sf::Vector2f& s)
		{
			halfWh = s;
			return this;
		}
		NamedButton* setName(const char* s)
		{
			text.setStr(s);
			return this;
		}
		NamedButton* setTextColor(Color color)
		{
			text.setColor(color);
			return this;
		}
		NamedButton* setTextSize(unsigned int s)
		{
			text.setSize(s);
			return this;
		}
		NamedButton* setTextOutlineColor(Color color)
		{
			text.setOutlineColor(color);
			return this;
		}
		NamedButton* setTextOutlineThickness(float s)
		{
			text.setOutlineThickness(s);
			return this;
		}
		NamedButton* setTextStyle(sf::Uint32 style)
		{
			text.setStyle(style);
			return this;
		}
		NamedButton* setTextOffset(const Vector2f& s)
		{
			text.setPos(s);
			return this;
		}


		Text text;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};
}