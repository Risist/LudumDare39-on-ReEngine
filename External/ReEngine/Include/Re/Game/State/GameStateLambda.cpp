#include <Re\Game\State\GameStateLambda.h>
#include <Re\Game\GameWorld.h>
#include <Re\Graphics\Graphics.h>

namespace Game
{
	void StateLambda::onStart()
	{
		_onStart();
	}

	void StateLambda::onExit()
	{
		_onExit();
	}

	State * StateLambda::onUpdate(sf::Time dt)
	{
		return _onUpdate(dt);
	}

	void StateLambda::defaultOnStart()
	{
		/// does nothing
	}

	void StateLambda::defaultOnExit()
	{
		Gui::gui.clear();
		world.clear();
	}

	State * StateLambda::defaultOnUpdate(sf::Time dt)
	{
		world.onUpdate(dt);
		cam.display(wnd);
		return nullptr;
	}

}