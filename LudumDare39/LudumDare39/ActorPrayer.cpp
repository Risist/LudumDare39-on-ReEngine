#include "ActorPrayer.h"
#include "ActorBlood.h"
#include "Layers.h"
#include "ActorBonfire.h"
#include "StateGame.h"

int ActorPrayer::n{0};
ActorPrayer::ActorPrayer()
{
}

void ActorPrayer::onInit()
{
	n++;
	/// graphics
	efModel = addEfect(new Efect::Model((ResId)1));
	if (StateGame::day > 2 && randRange(0, 1) > 0.8 )
	{
		agressive = true;
		efModel->modelsUpdate[7]->color.a = 255;
	}

	auto efAnim = addEfect(new Efect::AnimationManager(efModel->modelsUpdate));
	
	animWalk = &efAnim->addAnimation("anim_walk.txt")->getAnimation();
	animRule = &efAnim->addAnimation("anim_Rule.txt")->getAnimation();


	/// physics
	addEfect(new Efect::Rigidbody(25, 20));
	addEfect(new Efect::ColliderCircle(50.f));
	addEfect(new Efect::UpdateTransform());


	efHealth = addEfect(new Efect::Health(50))->setRegeneration(0, 0.6);
	addEfect(new Efect::SpawnOnDeath([]() { return new ActorBlood(); }))
		->setLayer(Game::Layers::blood);



	efMovement = addEfect(new Efect::MovementAim(50, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.006)));
	efRandomMovement = addEfect(new Efect::RandomMovement(efMovement), false)->setRadius(0,100.f)->setOffset(Vector2D(0,-100))->setTime(sf::seconds(0.2f), sf::seconds(0.75f));


	setMode(Mode::walkRandom);
}

void ActorPrayer::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);

	if (efMovement->getArrived() == false)
		animWalk->updateReturn();

	switch (mode)
	{
	case ActorPrayer::walkRandom:
		{
			static const float maxRadius = 1350;
			static const float minRadius = 1000;
			if (getPosition().getLenghtSq() > maxRadius*maxRadius)
			{
				efMovement->setDestination(Vector2D(), 0.1f);
			}
			else if (getPosition().getLenghtSq() < minRadius*minRadius)
			{
				efMovement->setDestination(getPosition().getNormalised()*maxRadius, 0.09f);
			}

			const float callDistance = 75;
			if (changeBehaviour.getElapsedTime() > changeBehaviourTime )
			{
				changeBehaviour.restart();
				//if (randRange(0.f, 1.f) > 0.25)
				setMode(Mode::collect);
			}

		}
		break;
	case ActorPrayer::collect:
		efMovement->setDestination(getPosition().getNormalised()*9000);
		if (getPosition().getLenghtSq() > 1350 * 1350 )
		{
			changeBehaviour.restart();
			setMode(sacrifice);
			efModel->modelsUpdate[4]->color.a = 255;
		}
		else if (changeBehaviour.getElapsedTime() > changeBehaviourTime)
		{
			changeBehaviour.restart();
			setMode(walkRandom);
		}
		break;

	case ActorPrayer::sacrifice:
		if (getPosition().getLenghtSq() < 200 * 200)
		{
			if (readyToBurn == false && animRule->updateReturn() )
				readyToBurn = true;
		}else
			efMovement->setDestination(Vector2D());

		if (changeBehaviour.getElapsedTime() > changeBehaviourTime ||
			(readyToBurn && ActorBonfire::bonfire->inflame(this, efMovement, efModel->modelsUpdate[4])))
		{
			readyToBurn = false;
			if (animRule->updateTowards(0))
			{
				changeBehaviour.restart();
				setMode(Mode::walkRandom);
			}
		}
		break;
	}
	

}

bool ActorPrayer::onDeath(sf::Time dt)
{
	Actor::onDeath(dt); 
	n--;
	return true;
}

void ActorPrayer::setMode(Mode s)
{
	mode = s;
	efRandomMovement->activated = (mode == walkRandom);

	switch (mode)
	{
	case ActorPrayer::walkRandom:
		
		if(StateGame::day == 1)
			changeBehaviourTime = sf::seconds(randRange(10.f, 60.f));
		else if (StateGame::day == 2)
			changeBehaviourTime = sf::seconds(randRange(10.f, 40.f));
		else if (StateGame::day == 3)
			changeBehaviourTime = sf::seconds(randRange(10.f, 20.f));

		efMovement->minimalDistance = 50;
		break;
	case ActorPrayer::sacrifice:
		efMovement->reset();
		efMovement->minimalDistance = 175;
		changeBehaviourTime = sf::seconds(randRange(7.5f, 12.5f));
		break;
	case ActorPrayer::collect:
		efMovement->minimalDistance = 175;
		changeBehaviourTime = sf::seconds(randRange(15.f, 20.f));
		break;
	}

}

