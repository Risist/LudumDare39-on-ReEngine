#pragma once
#include <Re\ReEngine.h>
#include "EfectLightSource.h"

class ActorBonfire : public Game::Actor
{
public:
	ActorBonfire();

	virtual void onInit() override;
	virtual void onUpdate(sf::Time dt) override;


	EfectLightSource *efLight;
private:
	Angle particleAngle;
};

