#pragma once
#include <Re\Ai\BehaviourTree\BtDecorator.h>

namespace Bt
{
	/// repeats behaviour loopN times
	class DecoratorLoop : public Decorator
	{
	public:
		DecoratorLoop(Base* _child, uint16 _loopN)
			:Decorator(_child), loopN(_loopN)
		{

		}

		void onEnter()
		{
			Decorator::onEnter();
			actualIt = 0;
		}
		State process()
		{
			State s = Decorator::process();
			++actualIt;
			return actualIt == loopN ? s : State::running;
		}

		/// how many times to repeat behaviour
		uint16 loopN;
	private:
		uint16 actualIt;
	};

	/// repeats behaviour until child return succed/ failiture
	/// then returns awaitedState
	class DecoratorLoopUntil : public Decorator
	{
	public:
		DecoratorLoopUntil(Base* _child, State _awaitedState = State::succed)
			:Decorator(_child), awaitedState(_awaitedState)
		{

		}
		State process()
		{
			State s = Decorator::process();
			return s == awaitedState ? s : State::running;
		}

		State awaitedState;
	};

}