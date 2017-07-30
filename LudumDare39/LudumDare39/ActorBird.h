#pragma once
#include <Re\ReEngine.h>
class ActorBird : public Game::Actor
{
public:
	static int n;
	ActorBird();

	enum Mode
	{
		WalkToPlayer,
		HideInShadows
	} mode;

	void setMode(Mode mode);

	virtual void onInit() override;
	virtual void onUpdate(sf::Time dt) override;
	virtual bool onDeath(sf::Time dt) override;

	Graphics::AnimationController *animFly;

	Efect::MovementAim *efMovement;
	Efect::RandomMovement *efRandomMovement;
	Efect::Health *efHealth;
	Efect::Model *efModel;

private:
	sf::Clock clockChangeBehaviour;
	sf::Time timeChangeBehaviour;
};

