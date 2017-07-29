#include "Player.h"
#include "Layers.h"

#include "ActorBlood.h"


void Player::onInit()
{
	Game::Actor::onInit();
	
	/// graphics
	addEfect(new Efect::Model((ResId)1 ));
	
	/// physics
	addEfect(new Efect::Rigidbody(25, 20));
	addEfect(new Efect::ColliderCircle(50.f));
	addEfect(new Efect::UpdateTransform());

	/// health
	// efHealth = addEfect(new Efect::Health())->setRegeneration(-0.1, 1);
	addEfect(new Efect::SpawnOnDeath([]() { return new ActorBlood(); }))
		->setLayer(Game::Layers::blood);

	healthBar = Gui::gui.add(new Gui::ProgressBar("gui_healthBar.txt"));


	/// 
	addEfect(new Efect::MouseMovement(25, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.005)));
	addEfect(new Efect::FollowCamera(Efect::FollowCamera::positionOnlySmooth))->setLerpPosition(0.125);

}

void Player::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);
	
	// healthBar->setProgress(efHealth->actual / efHealth->max);
}

bool Player::onDeath(sf::Time dt)
{
	Gui::gui.remove(healthBar);
	return true;
}
