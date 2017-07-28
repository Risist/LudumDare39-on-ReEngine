#include <Re\Game\State\GameState.h>
#include <Re\Game\GameWorld.h>

namespace Game
{
	State::State()
	{
	}

	void State::onStart()
	{
	}

	void State::onExit()
	{
		//gui.clear();
		Game::world.clear();
	}

}
