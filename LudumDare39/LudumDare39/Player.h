#pragma once
#include <Re\ReEngine.h>
#include <Re\Game\Efect\efects.h>


class Player : public Game::Actor
{
public:

	/// virtual overrides
	void onInit() override;
	void onUpdate(sf::Time dt) override;

	/// efect ptrs
};