#pragma once
#include <Re\Graphics\Gui\GuiButton.h>

namespace Gui
{

	/// checkbox class to hold boolean value
	/// works like normal button but holds state
	/// statePressed is used if b == true and no matter whether or not mouse is on button
	/// stateMouseOut is used when b == false
	/// stateMouseOn is used like in window
	/// lambda function is called when the object is pressed
	class CheckBox : public Button
	{
		virtual std::string getClassName() const override { return "CheckBox"; }
	public:
		CheckBox(const Vector2f& pos = Vector2f(), const Vector2f& halfWh = Vector2f(),
			function<void()> eventOnPress = []() {},
			State stateMouseOn = State(),
			State statePressed = State(),
			State stateMouseOut = State(),
			bool initialState = false
		);
		CheckBox(State constantState, const Vector2f& pos, const Vector2f& halfWh,
			function<void()> eventOnPress = []() {},
			bool initialState = false
		);
		CheckBox(const string& path) { deserialise(path); }

		virtual void update(RenderTarget& wnd, RenderStates states) override;

		/// setters
		CheckBox* setState(const State& s)
		{
			stateMouseOn = stateMouseOut = statePressed = s;
			return this;
		}
		CheckBox* setStateMouse(const State& s)
		{
			stateMouseOn = stateMouseOut = s;
			return this;
		}
		CheckBox* setStateMouseOn(const State& s)
		{
			stateMouseOn = s;
			return this;
		}
		CheckBox* setStateMouseOut(const State& s)
		{
			stateMouseOut = s;
			return this;
		}
		CheckBox* setStatePressed(const State& s)
		{
			statePressed = s;
			return this;
		}
		CheckBox* setEvent(function<void()> ev)
		{
			eventOnPress = ev;
			return this;
		}
		CheckBox* setPos(const sf::Vector2f& _new)
		{
			return (CheckBox*)Base::setPos(_new);
		}
		CheckBox* setInitial(bool s)
		{
			b = s;
			return this;
		}


		/// value of field
		bool b;
	private:
		bool canBeActivatedAgain;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}