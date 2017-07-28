#pragma once
#include <Re\Graphics\Gui\GuiMenu.h>
#include <Re\Graphics\Gui\GuiButton.h>

namespace Gui
{

	class ScrollBar : public Menu
	{
		virtual std::string getClassName() const override { return "ScrollBar"; }
	public:
		ScrollBar(sf::Vector2f& position, sf::Vector2f& halfWh = Vector2f(), float32 scrollLenght = 10.f,
			State stateBackground = State(),
			State stateScrollOn = State(), State stateScrollPressed = State(),
			State stateScrollOut = State());
		ScrollBar(
			State stateBackground = State(),
			State stateScroll = State(),
			sf::Vector2f& position = sf::Vector2f(), sf::Vector2f& halfWh = sf::Vector2f(), float32 scrollLenght = 10.f);

		virtual void update(sf::RenderTarget& target, sf::RenderStates states) override;

		/// in which direction the scroll can be moved
		enum Direction
		{
			left,
			up
		}direction;


		/// setters
		ScrollBar* setStateBackground(const State& s)
		{
			bBackground->setState(s);
			return this;
		}
		ScrollBar* setStateScroll(const State& s)
		{
			bScroll->setState(s);
			return this;
		}
		ScrollBar* setStateScrollMouseOn(const State& s)
		{
			bScroll->setStateMouseOn(s);
			return this;
		}
		ScrollBar* setStateScrollMouseOut(const State& s)
		{
			bScroll->setStateMouseOut(s);
			return this;
		}
		ScrollBar* setStateScrollMouse(const State& s)
		{
			bScroll->setStateMouse(s);
			return this;
		}
		ScrollBar* setStateScrollPressed(const State& s)
		{
			bScroll->setStateMouseOn(s);
			return this;
		}

		ScrollBar* setDirection(Direction s)
		{
			direction = s;
			return this;
		}
		ScrollBar* setProgress(float32 s)
		{
			progress = clamp(s, 0.f, 1.f);
			needToBeUpdated = true;
			return this;
		}
		ScrollBar* setEvent(function<void(float32&)> ev)
		{
			eventUpdateProgress = ev;
			return this;
		}
		ScrollBar* set(const Vector2f& halfWh, float32 scrollLenght)
		{
			bBackground->halfWh = halfWh;

			if (direction == Direction::left)
			{
				bScroll->halfWh.y = halfWh.y;
				bScroll->halfWh.x = scrollLenght;
			}
			else if (direction == Direction::up)
			{
				bScroll->halfWh.x = halfWh.x;
				bScroll->halfWh.y = scrollLenght;
			}

			return this;
		}
		ScrollBar* setPos(const sf::Vector2f& _new)
		{
			return (ScrollBar*)Base::setPos(_new);
		}
		


		/// costant part of the scrollbar
		shared_ptr<Button> bBackground;
		/// movable part of the scrollbar
		shared_ptr<Button> bScroll;

		
		float32 getProgres() const { return progress; }

		/// event called when the progress is changed (by buttons)
		function<void(float32&)> eventUpdateProgress{ [](float32&) {} };
	private:
		/// progress of the bar
		/// in range of [0,1] inclusive
		float32 progress;
		/// to avoid loop calls of eventUpdateProgress
		bool needToBeUpdated{true};
	private:
		bool scrollPressed;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};



}