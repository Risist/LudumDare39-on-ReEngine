#pragma once
#include <Re\ReEngine.h>
#include <Re\Game\Efect\efects.h>

class ActorBlood : public Game::Actor
{
public:
	ActorBlood(ResId indexSound);

	/// virtual override
	virtual void onInit() override; 
	virtual void onUpdate(sf::Time dt) override;

	/// efect ptrs
	Efect::Model *efModel;

private:
	ResId indexSound;
	sf::Sound deathSound;
};

