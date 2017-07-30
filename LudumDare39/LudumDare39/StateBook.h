#pragma once
#include <Re\ReEngine.h>
class StateBook : public Game::State
{
public:
	StateBook( int day = 1);

	/// overrided events
	virtual void onStart() override;
	virtual Game::State* onUpdate(sf::Time dt) override;
	virtual void onExit() override;

	sf::Music tale;
	int day;
};

