#pragma once
#include <Re\Game\State\GameState.h>


namespace Game
{

	// takes care over managing states of the game
	// supports only one state at the time, the other are removed
	// TODO version that is capable to hold many states and quickly move between them
	class StateManager
	{
	public:
		StateManager();
		~StateManager();

		/// update actual state
		/// dt is time elapsed from last update
		void onUpdate( sf::Time dt = sf::seconds(1) );

		/// sets new state and removes currently existing one 
		/// do not try to change state twice in one frame
		/// automatically called by 
		void setState(State* state)
		{
			assert(nextToActivate == nullptr);
			nextToActivate = state;
		}

	private:
		State* activatedState;
		State* nextToActivate;
	};
	extern StateManager stateManager;

}
