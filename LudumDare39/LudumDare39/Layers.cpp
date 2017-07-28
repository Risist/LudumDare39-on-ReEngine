#include "Layers.h"
#include <Re\Game\GameWorld.h>

namespace Game
{
	namespace Layers
	{
		void init()
		{
			background = world.addActor(new Layer());
			blood = world.addActor(new Layer());
			bullet = world.addActor(new Layer());
			obstacle = world.addActor(new Layer());
			character = world.addActor(new Layer());
		}

		Layer* background = nullptr;
		Layer* blood = nullptr;
		Layer* bullet = nullptr;
		Layer* obstacle = nullptr;
		Layer* character = nullptr;
	}
}