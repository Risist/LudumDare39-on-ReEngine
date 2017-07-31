#include "ActorPrayer.h"
#include "ActorBlood.h"
#include "Layers.h"
#include "ActorBonfire.h"
#include "StateGame.h"
#include "ActorFireball.h"

int ActorPrayer::n{0};
ActorPrayer::ActorPrayer(bool _agressive) : agressive(_agressive)
{
}

void ActorPrayer::onInit()
{
	n++;
	/// walking sound

#ifndef RELEASE_PATHS
	walking_sound.openFromFile("..\\..\\Resources\\Audio\\walking.wav");
#else
	walking_sound.openFromFile("Resources\\Audio\\walking.wav");
#endif

	walking_sound.setPitch(randRange(0.9,1.1));
	walking_sound.setVolume(100);
	walking_sound.setLoop(true);
	walking_sound.setMinDistance(200.f);
	walking_sound.setAttenuation(0.25f);

	dmgSound.setBuffer(soundInst[2]);
	dmgSound.setPitch(randRange(0.9, 1.1));
	dmgSound.setVolume(60);
	dmgSound.setMinDistance(200.f);
	dmgSound.setAttenuation(0.25f);


	
	/// graphics
	efModel = addEfect(new Efect::Model((ResId)1));
	if (agressive )
	{
		efModel->modelsUpdate[7]->color.a = 255;
	}

	auto efAnim = addEfect(new Efect::AnimationManager(efModel->modelsUpdate));
	
	animWalk = &efAnim->addAnimation("anim_walk.txt")->getAnimation();
	animRule = &efAnim->addAnimation("anim_Rule.txt")->getAnimation();
	animCast = &efAnim->addAnimation("anim_Cast.txt")->getAnimation();


	/// physics
	addEfect(new Efect::Rigidbody(25, 20));
	addEfect(new Efect::ColliderCircle(50.f));
	addEfect(new Efect::UpdateTransform());


	efHealth = addEfect(new Efect::Health(agressive ? 200 : 50))->setRegeneration(0, 0.6)
		->setDamageReaction([&](float32, Game::Actor* owner) {if (owner != this && dmgSound.getStatus() != Sound::Playing) dmgSound.play(); });
	addEfect(new Efect::SpawnOnDeath([]() { return new ActorBlood(3); }))
		->setLayer(Game::Layers::blood);



	efMovement = addEfect(new Efect::MovementAim(50, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.014)));
	efRandomMovement = addEfect(new Efect::RandomMovement(efMovement), false)->setRadius(0,100.f)->setOffset(Vector2D(0,-100))->setTime(sf::seconds(0.2f), sf::seconds(0.75f));


	setMode(Mode::walkRandom);
	
	if (agressive)
	{
		addEfect(new Efect::Throw)->addData([this]()
		{
			readyToShoot = false;
			return new ActorFireball(Angle::zero, randRange(0.8,0.95));
		}, [&]() {return readyToShoot; })
			->setDataLayer(Game::Layers::bullet)
			->setDataTransform(Vector2D(0, -150), Angle::zero);
	}
}

void ActorPrayer::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);

	walking_sound.setPosition(sf::Vector3f(getPosition().x, 0.f, getPosition().y));
	dmgSound.setPosition(sf::Vector3f(getPosition().x, 0.f, getPosition().y));

	if (efMovement->getArrived() == false)
	{
		if (is_walking_activated)
		{
			walking_sound.play();
			is_walking_activated = false;
		}
		animWalk->updateReturn();
	}
	else
	{
		is_walking_activated = true;
		walking_sound.pause();
	}

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

			if (changeBehaviour.getElapsedTime() > changeBehaviourTime )
			{
				changeBehaviour.restart();
				if (agressive && randRange(0.f, 1.f) > 0.25)
					setMode(Mode::atack);
				else
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
			efModel->modelsUpdate[4]->color = Color_f(randRange(100, 155), randRange(100, 155), randRange(100, 155), 200);
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
			if (readyToBurn == false && animRule->updateReturn())
			{
				readyToBurn = true;
				ActorBonfire::bonfire->inflame(this, efMovement, efModel->modelsUpdate[4]);
			}
		}
		else
		{
			efMovement->setDestination(Vector2D());
			if (changeBehaviour.getElapsedTime() > changeBehaviourTime)
			{
				changeBehaviour.restart();
				readyToBurn = false;
				waitingFire = false;
				setMode(Mode::walkRandom);
				return;
			}
		}

		if (readyToBurn)
		{
			if (waitingFire)
			{
				if (changeBehaviour.getElapsedTime() > changeBehaviourTime)
				{
					changeBehaviour.restart();
					readyToBurn = false;
					waitingFire = false;
					setMode(Mode::walkRandom);
					return;
				}
			}
			else if (animRule->updateReturn())
				waitingFire = true;
		}

		break;
	case ActorPrayer::atack:
		efMovement->efRotDir->direction = (Player::player->getPosition() - getPosition()).angle();
		
		
		if (readyToBurn == false )
		{
			if (animCast->updateInRange())
			{
				readyToShoot = true;
				readyToBurn = true;
			}
		}
		else
		{
			if (animCast->updateTowards(0))
			{
				readyToBurn = false;
				setMode(walkRandom);
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
			changeBehaviourTime = sf::seconds(randRange(15.f, 60.f));
		else if (StateGame::day == 2)
			changeBehaviourTime = sf::seconds(randRange(5.f, 15.f));
		else if (StateGame::day == 3)
			changeBehaviourTime = sf::seconds(randRange(1.f, 8.f));

		efMovement->minimalDistance = 50;
		break;
	case ActorPrayer::sacrifice:
		efMovement->reset();
		efMovement->minimalDistance = 175;
		changeBehaviourTime = sf::seconds(randRange(4.f, 7.f));
		break;
	case ActorPrayer::collect:
		efMovement->minimalDistance = 175;
		changeBehaviourTime = sf::seconds(randRange(3.f, 4.f));
		break;
	case ActorPrayer::atack:
		efMovement->reset();
		readyToBurn = false;
		break;
	}

}

