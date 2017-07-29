#pragma once
#include <Re\ReEngine.h>


class ActorPrayer : public Game::Actor
{
public:
	ActorPrayer();

	virtual void onInit() override;
	virtual void onUpdate(sf::Time dt) override;

	Efect::MovementAim *efMovement;
};

