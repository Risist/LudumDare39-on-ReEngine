#include "ActorBlood.h"

ActorBlood::ActorBlood(ResId indexSound_) : indexSound(indexSound_)
{
}
static const sf::Time bloodLifeTime = sf::seconds(50);

void ActorBlood::onInit()
{
	Game::Actor::onInit();

	efModel = addEfect(new Efect::Model((ResId)3));
	addEfect(new Efect::RemoveAfterDelay(bloodLifeTime ));

	deathSound.setBuffer(soundInst[2]);
	deathSound.setPitch(randRange(0.9, 1.1));
	deathSound.setVolume(100);
	deathSound.setMinDistance(100.f);
	deathSound.setAttenuation(1.f);
	deathSound.play();

}

void ActorBlood::onUpdate(sf::Time dt)
{
	Game::Actor::onUpdate(dt);
	
	deathSound.setPosition(sf::Vector3f(getPosition().x, 0.f, getPosition().y));

	efModel->model.color.a = efModel->model.color.a * 0.9995;

}
