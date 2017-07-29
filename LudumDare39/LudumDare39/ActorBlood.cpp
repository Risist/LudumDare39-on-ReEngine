#include "ActorBlood.h"


ActorBlood::ActorBlood()
{
}
static const sf::Time bloodLifeTime = sf::seconds(50);

void ActorBlood::onInit()
{
	Game::Actor::onInit();

	efModel = addEfect(new Efect::Model((ResId)3));
	addEfect(new Efect::RemoveAfterDelay(bloodLifeTime ));
}

void ActorBlood::onUpdate(sf::Time dt)
{
	Game::Actor::onUpdate(dt);


	efModel->model.color.a = efModel->model.color.a * 0.9995;

}
