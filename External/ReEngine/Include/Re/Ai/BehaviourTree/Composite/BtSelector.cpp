#include <Re\Ai\BehaviourTree\Composite\BtSelector.h>

namespace Bt
{
	Composite::State Selector::process()
	{
		State s = (*actualProceedElement)->process();

		if (s == State::running || s == State::succed)
			return s;

		if (actualProceedElement != elements.end())
		{
			(*actualProceedElement)->onExit();
			actualProceedElement = elements.begin();
			(*actualProceedElement)->onEnter();
			return State::running;
		}

		return State::failiture;
	}
}