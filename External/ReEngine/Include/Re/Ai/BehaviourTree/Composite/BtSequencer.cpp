#include <Re\Ai\BehaviourTree\Composite\BtSequencer.h>

namespace Bt
{




	Composite::State Sequencer::process()
	{
		State s = (*actualProceedElement)->process();
		
		if (s == State::running || s == State::failiture)
			return s;

		if (actualProceedElement != elements.end())
		{
			(*actualProceedElement)->onExit();
			actualProceedElement = elements.begin();
			(*actualProceedElement)->onEnter();
			return State::running;
		}

		return State::succed;
	}

}