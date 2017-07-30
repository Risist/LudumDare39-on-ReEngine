#pragma once
#include <Re\ReEngine.h>


class ActorBrushwood : public Game::Actor
{
public:
	ActorBrushwood();

	void onInit() override;
	void onUpdate(sf::Time dt) override;

	bool collect(Game::Actor* collector, Efect::MovementAim* efMovement, Graphics::Model* handBurshwood);

};

