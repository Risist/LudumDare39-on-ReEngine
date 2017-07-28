#pragma once
#include <Re\Graphics\Gui\GuiBase.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	/// Data depended on button state packed in struct
	struct State
	{
		State(const sf::Color& _cl = Color::White, ResId tsId = 0);
		State(ResId tsId, const sf::Color& _cl);
		void setTexture(ResId id)
		{
			tsId = id;
			ts = tsInst[id];
		}
		sf::Color cl;
		ResId tsId;
		ResourceManager::TextureInstance ts;
	};
	class Button : public Base
	{
		virtual std::string getClassName() const override { return "Button"; }
	public:
		Button(const Vector2f& pos = Vector2f(), const Vector2f& halfWh = Vector2f(),
			function<void()> eventOnPress = []() {},
			State stateMouseOn = State(),
			State statePressed = State(),
			State stateMouseOut = State()
		);
		Button(State constantState, const Vector2f& pos, const Vector2f& halfWh,
			function<void()> eventOnPress = []() {}
		);
		Button(const string& path) { deserialise(path); }
		
		virtual void update(sf::RenderTarget& target, sf::RenderStates states) override;

		Button* setState(const State& s)
		{
			stateMouseOn = stateMouseOut = statePressed = s;
			return this;
		}
		Button* setStateMouse(const State& s)
		{
			stateMouseOn = stateMouseOut = s;
			return this;
		}
		Button* setStateMouseOn(const State& s)
		{
			stateMouseOn = s;
			return this;
		}
		Button* setStateMouseOut(const State& s)
		{
			stateMouseOut = s;
			return this;
		}
		Button* setStatePressed(const State& s)
		{
			statePressed = s;
			return this;
		}
		Button* setEvent(function<void()> ev)
		{
			eventOnPress = ev;
			return this;
		}
		Button* setPos(const sf::Vector2f& _new)
		{
			return (Button*)Base::setPos(_new);
		}
		Button* setHalfWh(const sf::Vector2f& s)
		{
			halfWh = s;
			return this;
		}

		/// Color & texture for each state:
		State stateMouseOn; ///<	mouse is on the button
		State statePressed; ///<	button is pressed
		State stateMouseOut;///<	mouse is not on the button

		/// what happeneds when button is pressed?
		function<void()> eventOnPress;

	protected:
		bool isMouseOnWindow() const;

	private:
		bool canBeActivatedAgain;
		Clock clock; 
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}