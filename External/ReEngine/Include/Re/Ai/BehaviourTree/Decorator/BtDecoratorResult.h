#pragma once
/// decorators which changes returned State

#include <Re\Ai\BehaviourTree\BtDecorator.h>
namespace Bt
{
	/// inverses returned state
	class DecoratorInverseResult : public Decorator
	{
	public:
		DecoratorInverseResult(Base* _child)
			:Decorator(_child)
		{

		}

		State process() override
		{
			State s = child->process();
			if (s == State::running)
				return State::running;
			else if (s == State::failiture)
				return State::succed;
			else
				return State::failiture;
		}
	};

	class DecoratorConstResult : public Decorator
	{
	public:
		DecoratorConstResult(Base* _child, State _stateToReturn)
			:Decorator(_child), stateToReturn(_stateToReturn)
		{

		}

		State process() override
		{
			child->process();
			return stateToReturn;
		}

		State stateToReturn;
	};
}