#pragma once
#include <Re\Game\Actor\GameLayer.h>

namespace Game
{
	/// layers used to specify order of update, rendering ect
	namespace Layers
	{
		/// adds layers to world
		/// call before using layers
		void init();

		extern Layer* background;
		extern Layer* blood;
		extern Layer* bullet;
		extern Layer* obstacle;
		extern Layer* character;
	}
}