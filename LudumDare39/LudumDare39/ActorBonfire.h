#pragma once
#include <Re\ReEngine.h>
#include "EfectLightSource.h"

class ActorBonfire : public Game::Actor
{
public:
	static ActorBonfire *bonfire;
	ActorBonfire();

	virtual void onInit() override;
	virtual void onUpdate(sf::Time dt) override;


	bool inflame(Game::Actor* creator, Efect::MovementAim* efMovement, Graphics::Model* burshwood);

	EfectLightSource *efLight;
	Efect::Particle *efParticle;
	Efect::DamageOnCollision *efDmg;


	float actualIntensitivity;
private:
	Angle particleAngle;
	Clock clockChangeRate;
	Clock clockShoot;
};

