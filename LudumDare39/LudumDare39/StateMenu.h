#pragma once
#include <Re\ReEngine.h>

class StateMenu : public Game::State
{
public:
	StateMenu();

	/// overrided events
	virtual void onStart() override;
	virtual Game::State* onUpdate(sf::Time dt) override;
	virtual void onExit() override;

};
