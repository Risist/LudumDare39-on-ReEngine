#include "ActorBird.h"
#include "ActorBlood.h"
#include "Layers.h"
#include "Player.h"

int ActorBird::n = 0;

ActorBird::ActorBird()
{
}

void ActorBird::onInit()
{
	++n;
	Actor::onInit();

	efModel = addEfect(new Efect::Model(8));
	auto efAnim = addEfect(new Efect::AnimationManager(efModel->modelsUpdate));

	animFly = &efAnim->addAnimation("anim_birdFly.txt")->getAnimation();
	/// physics
	addEfect(new Efect::Rigidbody(7, 20));
	addEfect(new Efect::ColliderCircle(50.f));
	addEfect(new Efect::UpdateTransform());
	


	efHealth = addEfect(new Efect::Health(50))->setRegeneration(0, 0.6);
	addEfect(new Efect::SpawnOnDeath([]() { return new ActorBlood(); }))
		->setLayer(Game::Layers::blood);
	addEfect(new Efect::DamageOnCollision(2))->allowdedToDeal = [](Game::Actor& other, b2Contact&) { return !dynamic_cast<ActorBird*>(&other); };

	efMovement = addEfect(new Efect::MovementAim(55, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.025)));
	efRandomMovement = addEfect(new Efect::RandomMovement(efMovement))
		->setRadius(100.f, 300.f)->setOffset(Vector2D(0, -100))->setTime(sf::seconds(0.5f), sf::seconds(0.95f));

	setMode(Mode::HideInShadows);
}

void ActorBird::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);

	if (efMovement->getInfluence().getLenghtSq() < efMovement->minimalDistance * efMovement->minimalDistance)
		animFly->updateInRange(1.5);
	else 
		animFly->updateInRange(-1);

	switch (mode)
	{
	case ActorBird::WalkToPlayer:
		efMovement->setDestination(Player::player->getPosition(), 10.f);
		if (clockChangeBehaviour.getElapsedTime() > timeChangeBehaviour || 
			(getPosition()- Player::player->getPosition()).getLenghtSq() < 100 * 100)
			setMode(HideInShadows);
		break;
	case ActorBird::HideInShadows:
		if (getPosition().getLenghtSq() < 1200 * 1200)
		{
			efMovement->setDestination(getPosition().getNormalised() * 2000, 0.1f);
		}
		if (clockChangeBehaviour.getElapsedTime() > timeChangeBehaviour)
			setMode(WalkToPlayer);
		break;
	}
}

bool ActorBird::onDeath(sf::Time dt)
{
	Actor::onDeath(dt);
	--n;
	return true;
}


void ActorBird::setMode(Mode _mode)
{
	mode = _mode;
	clockChangeBehaviour.restart();

	switch (mode)
	{
	case ActorBird::WalkToPlayer:
		timeChangeBehaviour = sf::seconds(randRange(2.5f, 5.f));
		break;
	case ActorBird::HideInShadows:
		timeChangeBehaviour = sf::seconds(randRange(4.f, 7.f));
		break;
	}
}

