#pragma once
#include <Re\Graphics\Gui\GuiMenu.h>
#include <Re\Graphics\Gui\GuiButton.h>
#include <Re\Graphics\Gui\GuiText.h>

/*


---------------------------------
|		|				|		|
|	-	|				|	+	|
|		|				|		|
---------------------------------
*/

namespace Gui
{
	class SetBar : public Menu
	{
		virtual std::string getClassName() const override { return "SetBar"; }
	public:
		SetBar();
		SetBar(const char* path);

		virtual void update(RenderTarget& wnd, RenderStates states) override;

		/// in which way the bar is oriented
		enum Direction
		{
			left,
			up
		}direction;
		
		/// setters
		SetBar* setPos(const Vector2f& s)
		{
			pos = s;
			return this;
		}
		SetBar* setStateBackground(const State& state)
		{
			bBackground->setState(state);
			return this;
		}
		SetBar* setStatePlus(const State& state)
		{
			bPlus->setState(state);
			return this;
		}
		SetBar* setStatePlus(const State& stateOn, const State& statePress, const State& stateOut = State())
		{
			bPlus->setStateMouseOn(stateOn)
				->setStateMouseOut(stateOut)
				->setStatePressed(statePress);
			return this;
		}
		SetBar* setStateMinus(const State& state)
		{
			bMinus->setState(state);
			return this;
		}
		SetBar* setStateMinus(const State& stateOn, const State& statePress, const State& stateOut = State())
		{
			bMinus->setStateMouseOn(stateOn)
				->setStateMouseOut(stateOut)
				->setStatePressed(statePress);
			return this;
		}
		SetBar* setStateSign(const State& state)
		{
			bPlus->setState(state);
			bMinus->setState(state);
			return this;
		}
		SetBar* setStateSign(const State& stateOn, const State& statePress, const State& stateOut = State())
		{
			bPlus->setStateMouseOn(stateOn)
				->setStateMouseOut(stateOut)
				->setStatePressed(statePress);
			bMinus->setStateMouseOn(stateOn)
				->setStateMouseOut(stateOut)
				->setStatePressed(statePress);
			return this;
		}
		SetBar* setName(const string& s)
		{
			name = s;
			return this;
		}
		SetBar* setProgress(float32 s)
		{
			progress = clamp(s, minimalValue, maximalValue);
			needToBeUpdated = true;
			return this;
		}
		SetBar* setMinMax(float32 min, float32 max, float32 initial)
		{
			minimalValue = min;
			maximalValue = max;
			initialValue = initial;
			return this;
		}
		SetBar* setEvent(function<void(float32&)> ev)
		{
			eventUpdateProgress = ev;
			return this;
		}

		SetBar* setInitial(float32 s)
		{
			initialValue = s;
			return this;
		}
		SetBar* setIncrease(thor::Distribution<float32> s)
		{
			increaseValue = s;
			return this;
		}
		SetBar* setEventPlus(function<bool()> s)
		{
			addictionalPressPlus = s;
			return this;
		}
		SetBar* setEventMinus(function<bool()> s)
		{
			addictionalPressMinus = s;
			return this;
		}



		shared_ptr<Button> bPlus; 
		shared_ptr<Button> bMinus;
		shared_ptr<Button> bBackground;
		shared_ptr<Text> tText;

		string name;


		/// event called when the progress is changed by buttons
		/// argument is actual progress
		function<void(float32&)> eventUpdateProgress{ [](float32&) {} };
		thor::Distribution<float32> increaseValue{ 1.f };
		function<bool()> addictionalPressPlus{ []() {return false; } };
		function<bool()> addictionalPressMinus{ []() {return false; } };
		
		float32 getProgres() const { return progress; }

		float32 initialValue{0};
		float32 minimalValue;
		float32 maximalValue;

	private:
		float32 progress{ 0 };
		/// to avoid loop calls of eventUpdateProgress;
		bool needToBeUpdated{true};
		Control::Timer timerPress;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


}