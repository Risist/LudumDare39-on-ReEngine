#pragma once
#include <Re\ReEngine.h>

class StateCredits : public Game::State
{
public:
	StateCredits();

	/// overrided events
	virtual void onStart() override;
	virtual Game::State* onUpdate(sf::Time dt) override;
	virtual void onExit() override;

};
