#pragma once
#include <Re\ReEngine.h>

class StateDeath : public Game::State
{
public:
	StateDeath();

	/// overrided events
	virtual void onStart() override;
	virtual Game::State* onUpdate(sf::Time dt) override;
	virtual void onExit() override;


};

