#pragma once
#include <Re\Ai\BehaviourTree\BtDecorator.h>

namespace Bt
{
	class DecoratorForTime : public Decorator
	{
	public:
		DecoratorForTime(Base* _child, sf::Time _untilTime)
			:Decorator(_child), untilTime(_untilTime)
		{

		}
		void onEnter()
		{
			Decorator::onEnter();
			clock.restart();
		}

		State process()
		{
			State s = Decorator::process();
			return clock.getElapsedTime() >= untilTime ? s : State::running;
		}

		sf::Time untilTime;
	private:
		Clock clock;
	};

	/// allows to call child only once per waitTime
	class DecoratorCooldown : public Decorator
	{
	public:
		DecoratorCooldown(Base* _child, sf::Time _waitTime)
			:Decorator(_child), waitTime(_waitTime)
		{

		}
		State process()
		{
			if (clock.getElapsedTime() >= waitTime)
			{
				clock.restart();
				sf::Keyboard
				return Decorator::process();
			}
			return State::failiture;
		}

		sf::Time waitTime;
	private:
		Clock clock;
	};

}