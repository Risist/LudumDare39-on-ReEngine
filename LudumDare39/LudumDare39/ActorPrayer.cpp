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


	addEfect(new Efect::Health(50))->setRegeneration(0, 0.6);
	addEfect(new Efect::SpawnOnDeath([]() { return new ActorBlood(); }))
		->setLayer(Game::Layers::blood);



	efMovement = addEfect(new Efect::MovementAim(40, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.005)));
	addEfect(new Efect::RandomMovement(efMovement))->setRadius(0,100.f)->setOffset(Vector2D(0,-100))->setTime(sf::seconds(0.2f), sf::seconds(0.75f));
}

void ActorPrayer::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);

	static const float maxRadius = 1250;
	static const float minRadius = 1000;
	if (getPosition().getLenghtSq() > maxRadius*maxRadius)
	{
		efMovement->setDestination(Vector2D(), 0.1f);
	}
	else if (getPosition().getLenghtSq() < minRadius*minRadius)
	{
		efMovement->setDestination(getPosition().getNormalised()*maxRadius, 0.09f);
	}

}

