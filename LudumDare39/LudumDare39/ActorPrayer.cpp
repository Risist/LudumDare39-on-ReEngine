#include "ActorPrayer.h"
#include "ActorBlood.h"
#include "Layers.h"



ActorPrayer::ActorPrayer()
{
}

void ActorPrayer::onInit()
{
	/// graphics
	addEfect(new Efect::Model((ResId)1));

	/// physics
	addEfect(new Efect::Rigidbody(25, 20));
	addEfect(new Efect::ColliderCircle(50.f));
	addEfect(new Efect::UpdateTransform());


	addEfect(new Efect::Health())->setRegeneration(0, 0.95);
	addEfect(new Efect::SpawnOnDeath([]() { return new ActorBlood(); }))
		->setLayer(Game::Layers::blood);



	auto efMovement = addEfect(new Efect::MovementAim(40, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.005)));
	addEfect(new Efect::RandomMovement(efMovement))->setRadius(0,100.f)->setOffset(Vector2D(0,-100));
}

void ActorPrayer::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);
}

