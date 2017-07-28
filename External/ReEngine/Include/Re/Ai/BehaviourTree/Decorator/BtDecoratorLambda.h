#pragma once
#include <Re\Ai\BehaviourTree\BtDecorator.h>

namespace Bt
{
	class DecoratorLambda : public Decorator
	{
	public:
		DecoratorLambda(Base* _child)
			: Decorator(_child)
		{
		}

		void onEnter() override
		{
			child->onEnter();
			eventOnEnter();
		}
		void onExit() override
		{
			child->onExit();
			eventOnExit();
		}
		State process()
		{
			child->process();
			return eventProcess();
		}

		/// functions for easier initialization
		DecoratorLambda* setOnEnter(function<void()> _eventOnEnter)
		{
			eventOnEnter = _eventOnEnter;
			return this;
		}
		DecoratorLambda* setOnExit(function<void()> _eventOnExit)
		{
			eventOnExit = _eventOnExit;
			return this;
		}
		DecoratorLambda* setProcess(function<State()> _eventProcess)
		{
			eventProcess = _eventProcess;
			return this;
		}

		function<void()> eventOnEnter{ []() {} };
		function<void()> eventOnExit{ []() {} };
		function<State()> eventProcess{ []() {return State::failiture;  } };
	};

}