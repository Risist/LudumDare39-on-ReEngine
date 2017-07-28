#pragma once
#include <Re\Ai\BehaviourTree\BtBase.h>

namespace Bt
{

	class LeafWait : public Base
	{
	public:
		LeafWait(sf::Time _waitTime)
			: waitTime(_waitTime)
		{

		}

		void onEnter() override
		{
			clock.restart();
		}
		State process() override
		{
			return clock.getElapsedTime() >= waitTime ? State::succed : State::running;
		}

		sf::Time waitTime;
	private:
		sf::Clock clock;
	};
}