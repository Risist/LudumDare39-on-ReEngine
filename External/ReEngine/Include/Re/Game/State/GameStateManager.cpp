#include "GameStateManager.h"


namespace Game
{
	StateManager stateManager;

	StateManager::StateManager()
		: activatedState(nullptr)
	{
	}

	StateManager::~StateManager()
	{
		if (activatedState != nullptr)
			delete activatedState;
		if (nextToActivate != nullptr)
			delete nextToActivate;
	}


	void StateManager::onUpdate( sf::Time dt)
	{
		/// change state
		if (nextToActivate != nullptr)
		{
			if (activatedState != nullptr)
			{
				activatedState->onExit();
				delete activatedState;
			}

			activatedState = nextToActivate;
			nextToActivate = nullptr;

			activatedState->onStart();
		}


		if (activatedState != nullptr)
		{
			auto it = activatedState->onUpdate(dt);
			if (it != nullptr)
				setState(it);
		}
	}
}

