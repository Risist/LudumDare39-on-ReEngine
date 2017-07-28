#pragma once
#include <Re\ReEngine.h>


class Player : public Game::Actor
{
public:

	/// virtual overrides
	void onInit() override;
	void onUpdate(sf::Time dt) override;
	bool onDeath(sf::Time dt) override;

	/// efect ptrs
	Efect::Health *efHealth;
	Gui::ProgressBar* healthBar;
};