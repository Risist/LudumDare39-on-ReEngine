#pragma once
#include <Re\Ai\BehaviourTree\BtBase.h>


namespace Bt
{
	/// class for fast creation of leafs
	/// mostly for prototyping because of little performance overhead
	/// and unavailability to reuse
	class LeafLambda : public Base
	{
	public:
		void onEnter() override
		{
			eventOnEnter();
		}
		void onExit() override
		{
			eventOnExit();
		}
		State process()
		{
			return eventProcess();
		}

		/// functions for easier initialization
		LeafLambda* setOnEnter(function<void()> _eventOnEnter)
		{
			eventOnEnter = _eventOnEnter;
			return this;
		}
		LeafLambda* setOnExit(function<void()> _eventOnExit)
		{
			eventOnExit = _eventOnExit;
			return this;
		}
		LeafLambda* setProcess(function<State()> _eventProcess)
		{
			eventProcess = _eventProcess;
			return this;
		}

		function<void()> eventOnEnter{ []() {} };
		function<void()> eventOnExit{ []() {} };
		function<State()> eventProcess{ []() {return State::failiture;  } };
	};


}