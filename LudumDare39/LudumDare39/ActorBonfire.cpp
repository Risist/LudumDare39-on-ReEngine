#include "ActorBonfire.h"
#include "ActorFireball.h"
#include "Layers.h"
#include "StateGame.h"

ActorBonfire *ActorBonfire::bonfire = nullptr;

ActorBonfire::ActorBonfire()
{
	actualIntensitivity = 0.975;
}

void ActorBonfire::onInit()
{
	Game::Actor::onInit();
	bonfire = this;
#ifndef RELEASE_PATHS
	bonfire_sound.openFromFile("..\\..\\Resources\\Audio\\bonfire_sound.wav");
#else
	bonfire_sound.openFromFile("Resources\\Audio\\bonfire_sound.wav");
#endif
	bonfire_sound.setVolume(100);
	bonfire_sound.setLoop(true);
	bonfire_sound.setPosition(sf::Vector3f(getPosition().x, 0, getPosition().y));
	bonfire_sound.setMinDistance(400.f);
	bonfire_sound.setAttenuation(0.5f);
	//bonfire_sound.play();
	

	addEfect(new Efect::Model((ResId)4));
	addEfect(new Efect::Rigidbody());
	addEfect(new Efect::ColliderCircle(75.f, 1.f, Vector2D(), true));
	efDmg = addEfect(new Efect::DamageOnCollision(10));

	efLight = addEfect(new EfectLightSource(125, 0.0003, actualIntensitivity));

	efParticle = addEfect(new Efect::Particle())->addEmitter(
		Emitter().setEmissionRate(120).setLifetime([]() { return sf::seconds(randRange(0.5f, 1.f)); })
			.setPosition([this](){
				particleAngle = randRange(Angle::zero, Angle::full);
				return getPosition() + (Vector2f)Vector2D(randRange(10.f, 40.f*actualIntensitivity), 0).getRotated(particleAngle);
			})
			.setScale([this]() { 
				float r = randRange(0.3f,0.7f)*actualIntensitivity;
				return Vector2D(r, r);
			})
			.setVelocity([this]() {	return (Vector2f)Vector2D(randRange(10.f, 60.f*actualIntensitivity), 0).getRotated(particleAngle); })
			.setRotation([](){		return randRange(0.f,360.f); })
			.setRotationSpeed([](){ return randRange(-10.5f,10.5f); })
			.setColor([this]() {
				float d = randRange(0.5f, 1.2f);
				return Color(200*d, 180*d*actualIntensitivity, 180*d*actualIntensitivity, randRange(30, 40));
			})
	)->setTexture(ResId(401));

	if (StateGame::day > 1)
	{
		addEfect(new Efect::Throw)->addData([this]()
		{
			if (clockShoot.getElapsedTime() > sf::seconds(0.05 / pow(actualIntensitivity, 20)) && actualIntensitivity > 0.8)
			{
				actualIntensitivity *= 0.99975;
				clockShoot.restart();
				return new ActorFireball(Vector2D(cam.mapPixelToCoords((Vector2D)Mouse::getPosition(wnd) - getPosition())).angle(), actualIntensitivity);
			}
			else return (ActorFireball*)nullptr;
		})
		->setDataLayer(Game::Layers::bullet);
	}
}

void ActorBonfire::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);
	//bar of bonfire's power
	sf::RectangleShape barOfPowerUnder(sf::Vector2f(200, 15));
	barOfPowerUnder.setOrigin(sf::Vector2f(barOfPowerUnder.getSize().x*0.5, barOfPowerUnder.getSize().y*0.5));
	barOfPowerUnder.setPosition(sf::Vector2f(getPosition().x, getPosition().y - 120));
	barOfPowerUnder.setFillColor(sf::Color(150, 150, 150, 180));
	cam.draw(barOfPowerUnder);
	float fillPercentage = (actualIntensitivity - 0.85 )*6.666666;
	//std::cout << actualIntensitivity << std::endl;
	sf::RectangleShape barOfPower(sf::Vector2f(clamp(fillPercentage,0.f,1.f) * 200, 15));
	barOfPower.setOrigin(sf::Vector2f(barOfPower.getSize().x*0.5, barOfPower.getSize().y*0.5));
	barOfPower.setPosition(sf::Vector2f(getPosition().x, getPosition().y - 120));
	barOfPower.setFillColor(sf::Color(75,20,20,220));
	cam.draw(barOfPower);

	efLight->maxIntensitivityRatio += randRange(-0.007, 0.009);
	efLight->maxIntensitivityRatio = clamp(efLight->maxIntensitivityRatio, 0.8f, actualIntensitivity);
	actualIntensitivity *= 0.99985;

	bonfire_sound.setPitch(0.3 + 0.7*powf(actualIntensitivity, 12));
	bonfire_sound.setVolume(100 * powf(actualIntensitivity, 12));
	
	efDmg->damage = 10 * actualIntensitivity;
	
	efParticle->particleSystem.clearEmitters();
	efParticle->addEmitter(
	Emitter().setEmissionRate(120* powf(actualIntensitivity,8)).setLifetime([]() { return sf::seconds(randRange(0.5f, 1.f)); })
		.setPosition([this](){
			particleAngle = randRange(Angle::zero, Angle::full);
			return getPosition() + (Vector2f)Vector2D(randRange(10.f, 40.f*actualIntensitivity), 0).getRotated(particleAngle);
		})
		.setScale([this]() { 
			float r = randRange(0.3f,0.7f)*actualIntensitivity;
			return Vector2D(r, r);
		})
		.setVelocity([this]() {	return (Vector2f)Vector2D(randRange(10.f, 60.f*actualIntensitivity), 0).getRotated(particleAngle); })
		.setRotation([](){		return randRange(0.f,360.f); })
		.setRotationSpeed([](){ return randRange(-10.5f,10.5f); })
		.setColor([this]() {
			float d = randRange(0.5f, 1.2f);
			return Color(200*d, 180*d*actualIntensitivity, 180*d*actualIntensitivity, randRange(30, 40));
		})
	)->setTexture(ResId(401));
}

bool ActorBonfire::inflame(Game::Actor * creator, Efect::MovementAim* efMovement, Graphics::Model * burshwood)
{
	static const float actionDistance = 350.f;
	
	//if ((creator->getPosition() - getPosition()).getLenghtSq() > actionDistance*actionDistance)
		//return false;

	if (burshwood->color.a == 0)
		return false;

	burshwood->color.a = 0;

	efMovement->reset();
	efMovement->efRotDir->direction = Vector2D(getPosition() - creator->getPosition()).angle();

	actualIntensitivity = clamp(actualIntensitivity +0.1f, 0.f, 1.f);

	return true;
}
