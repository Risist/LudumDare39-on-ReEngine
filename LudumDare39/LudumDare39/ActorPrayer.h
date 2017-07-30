#pragma once
#include <Re\ReEngine.h>


class ActorPrayer : public Game::Actor
{
public:
	static int n;
	ActorPrayer();

	enum Mode
	{
		walkRandom,
		collect,
		sacrifice
	}mode;

	void setMode(Mode s);

	virtual void onInit() override;
	virtual void onUpdate(sf::Time dt) override;
	virtual bool onDeath(sf::Time dt) override;


	Graphics::AnimationController *animWalk;
	Graphics::AnimationController *animRule;


	Efect::MovementAim *efMovement; 
	Efect::RandomMovement *efRandomMovement;
	Efect::Health *efHealth;
	Efect::Model *efModel;

	sf::Clock changeBehaviour;
	sf::Time changeBehaviourTime;

	bool agressive{false};
private:
	bool readyToBurn{false};
	bool is_walking_activated = true;
	sf::Music walking_sound;
};

