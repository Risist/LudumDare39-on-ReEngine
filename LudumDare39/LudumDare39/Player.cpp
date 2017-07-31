#include "Player.h"
#include "Layers.h"
#include "StateGame.h"

#include "ActorBlood.h"
#include "ActorBonfire.h"
#include "StateDeath.h"

#include "LightController.h"

Player *Player::player = nullptr;

void Player::onInit()
{
	player = this;
	Game::Actor::onInit();

	/// walking sound
	walking_sound.openFromFile("..\\..\\Resources\\Audio\\walking.wav");
	walking_sound.setPitch(randRange(0.9, 1.1));
	walking_sound.setVolume(100);
	walking_sound.setLoop(true);
	walking_sound.setMinDistance(0.f);    

	dmgSound.setBuffer(soundInst[2]);
	dmgSound.setVolume(60);
	dmgSound.setMinDistance(200.f);
	dmgSound.setAttenuation(0.25f);
	

	//for 3D sound
	sf::Listener::setDirection(sf::Vector3f(0.f, 0.f, -1.f));


	/// graphics
	efModel = addEfect(new Efect::Model((ResId)1 ));
	if (StateGame::day > 1)
	{
		efModel->modelsUpdate[7]->color.a = 255;
	}
	
	auto efAnim = addEfect(new Efect::AnimationManager(efModel->modelsUpdate));

	animCast = &efAnim->addAnimation("anim_cast.txt")->getAnimation();
	animWalk = &efAnim->addAnimation("anim_walk.txt")->getAnimation();
	animRule = &efAnim->addAnimation("anim_Rule.txt")->getAnimation();


	/// physics
	addEfect(new Efect::Rigidbody(25, 20));
	addEfect(new Efect::ColliderCircle(50.f));
	addEfect(new Efect::UpdateTransform());
	

	/// health
	efHealth = addEfect(new Efect::Health(70*StateGame::day))->setRegeneration(0, 0.6)
		->setDamageReaction([&](float32, Game::Actor* owner) {if (owner != this && dmgSound.getStatus() != Sound::Playing) dmgSound.play(); });

	addEfect(new Efect::SpawnOnDeath([]() { return new ActorBlood(); }))
		->setLayer(Game::Layers::blood);

	healthBarRight = Gui::gui.add(new Gui::ProgressBar("gui_healthBarRight.txt"));
	healthBarLeft = Gui::gui.add(new Gui::ProgressBar("gui_healthBarLeft.txt"));

	/// 
	efMovement = addEfect(new Efect::MouseMovement(50, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.014)));
	//efMovement = addEfect(new Efect::StaticMovement(40, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.005)));
	addEfect(new Efect::FollowCamera(Efect::FollowCamera::positionOnlySmooth))->setLerpPosition(0.125);

}

void Player::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);

	//for 3D sound
	sf::Listener::setPosition(sf::Vector3f(Player::player->getPosition().x, 0, Player::player->getPosition().y));
	walking_sound.setPosition(sf::Vector3f(getPosition().x, 0, getPosition().y));

	float light = sqrt(lightController.lastLightIntensitivitySq);
	if (light< 0.97f)
		efHealth->damage((0.97f - light)* 0.4f, this);
	else
		efHealth->heal((light - 0.97f) * 2., this);

	healthBarLeft->setProgress(efHealth->actual / efHealth->max);
	healthBarRight->setProgress(efHealth->actual / efHealth->max);
	
	if (efMovement->getArrived() == false)
	{
		if(is_walking_activated)
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


	static const float actionDistance = 125;
	if (actionMap.isActive("fire3") )
	{
		efMovement->reset();
		efMovement->efRotDir->direction = Vector2D( (Vector2D)cam.mapPixelToCoords((Vector2D)Mouse::getPosition(wnd)) - getPosition()).angle();
		
		animRule->updateInRange();

		if (((Vector2D)cam.mapPixelToCoords(Mouse::getPosition(wnd)) - ActorBonfire::bonfire->getPosition())
			.getLenghtSq() < actionDistance*actionDistance)
			if( getPosition().getLenghtSq() < 300 * 300)
			ActorBonfire::bonfire->inflame(this, efMovement, efModel->modelsUpdate[4]);

	}
	else
		animRule->updateInRange(-1);

	{
		if (actionMap.isActive("fire2"))
		{
			efMovement->reset();
			efMovement->efRotDir->direction = Vector2D((Vector2D)cam.mapPixelToCoords((Vector2D)Mouse::getPosition(wnd)) - getPosition()).angle();

			onAnimCast = true;
		}

		if (!onAnimCastBack && onAnimCast && animCast->updateInRange() && actionMap.isActive("fire2") == false)
			onAnimCastBack = true;

			
		if (onAnimCastBack && animCast->updateInRange(-1))
		{
			onAnimCastBack = false;
			onAnimCast = false;
		}
	}
}

bool Player::onDeath(sf::Time dt)
{
	Actor::onDeath(dt);
	Gui::gui.remove(healthBarLeft);
	Gui::gui.remove(healthBarRight);

	Game::stateManager.setState(new StateDeath);
	return true;
}
