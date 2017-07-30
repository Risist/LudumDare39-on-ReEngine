#pragma once
#include <Re\ReEngine.h>
#include "EfectLightSource.h"


class ActorFireball : public Game::Actor
{
public:
	ActorFireball(Angle direction, float power);

	virtual void onInit() override;
	virtual void onUpdate(sf::Time dt) override;



	EfectLightSource *efLight;
	Efect::Motor *efMotor;
	Angle direction;
	float power;
private:
	Angle particleAngle;
};

