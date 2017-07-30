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
	walking_sound.setPitch(0.95);
	walking_sound.setVolume(100);
	walking_sound.setLoop(true);
	walking_sound.setMinDistance(0.f);     
	

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
	efHealth = addEfect(new Efect::Health())->setRegeneration(0, 0.6);

	addEfect(new Efect::SpawnOnDeath([]() { return new ActorBlood(); }))
		->setLayer(Game::Layers::blood);

	healthBar = Gui::gui.add(new Gui::ProgressBar("gui_healthBar.txt"));
	rageBar = Gui::gui.add(new Gui::ProgressBar("gui_rageBar.txt"));


	/// 
	efMovement = addEfect(new Efect::MouseMovement(50, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.006)));
	//efMovement = addEfect(new Efect::StaticMovement(40, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.005)));
	addEfect(new Efect::FollowCamera(Efect::FollowCamera::positionOnlySmooth))->setLerpPosition(0.125);

}

void Player::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);

	//for 3D sound
	sf::Listener::setPosition(sf::Vector3f(Player::player->getPosition().x, 0, Player::player->getPosition().y));
	walking_sound.setPosition(sf::Vector3f(getPosition().x, 0, getPosition().y));

	efHealth->damage((0.915- lightController.lastLightIntensitivitySq)* 0.2,this);
	
	healthBar->setProgress(efHealth->actual / efHealth->max);
	
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
	Gui::gui.remove(healthBar);
	Gui::gui.remove(rageBar);
	Game::stateManager.setState(new StateDeath);
	return true;
}
