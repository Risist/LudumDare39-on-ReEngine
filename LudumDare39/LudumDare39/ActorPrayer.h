#pragma once
#include <Re\ReEngine.h>


class ActorPrayer : public Game::Actor
{
public:
	static int n;
	ActorPrayer(bool _agressive = false);

	enum Mode
	{
		walkRandom,
		collect,
		sacrifice,
		atack
	}mode;

	void setMode(Mode s);

	virtual void onInit() override;
	virtual void onUpdate(sf::Time dt) override;
	virtual bool onDeath(sf::Time dt) override;


	Graphics::AnimationController *animWalk;
	Graphics::AnimationController *animRule;
	Graphics::AnimationController *animCast;


	Efect::MovementAim *efMovement; 
	Efect::RandomMovement *efRandomMovement;
	Efect::Health *efHealth;
	Efect::Model *efModel;

	sf::Clock changeBehaviour;
	sf::Time changeBehaviourTime;

	bool agressive{false};
private:
	bool waitingFire{ false };
	bool readyToBurn{false};
	bool readyToShoot{false};
	bool is_walking_activated = true;
	sf::Music walking_sound;
	sf::Sound dmgSound;
};

