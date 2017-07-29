#include "ActorBonfire.h"
#include "ActorFireball.h"
#include "Layers.h"



ActorBonfire::ActorBonfire()
{
}

void ActorBonfire::onInit()
{
	Game::Actor::onInit();

	addEfect(new Efect::Model((ResId)4));
	addEfect(new Efect::Rigidbody());
	addEfect(new Efect::ColliderCircle(75.f, 1.f, Vector2D(), true));
	addEfect(new Efect::DamageOnCollision(10.75));

	efLight = addEfect(new EfectLightSource(0, 0.000325, 0.95));

	addEfect(new Efect::Particle())->addEmitter(
		Emitter().setEmissionRate(120).setLifetime([]() { return sf::seconds(randRange(0.5f, 1.f)); })
			.setPosition([&](){
				particleAngle = randRange(Angle::zero, Angle::full);
				return (Vector2f)Vector2D(randRange(10.f, 40.f), 0).getRotated(particleAngle); 
			})
			.setScale([]() { 
				float r = randRange(0.3f,0.7f);
				return Vector2D(r, r);
			})
			.setVelocity([&]() {	return (Vector2f)Vector2D(randRange(10.f, 60.f), 0).getRotated(particleAngle); })
			.setRotation([](){		return randRange(0.f,360.f); })
			.setRotationSpeed([](){ return randRange(-10.5f,10.5f); })
			.setColor([]() {
				float d = randRange(0.5f, 1.2f);
				return Color(200*d, 180*d, 180*d, randRange(30, 40)); 
			})
	)->setTexture(ResId(401));

			
	addEfect(new Efect::Throw)->addData([=]() 
	{
		return new ActorFireball(Vector2D(cam.mapPixelToCoords(Mouse::getPosition(wnd))).angle());
	})
		
		->setDataLayer(Game::Layers::bullet)
		;
}

void ActorBonfire::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);

	efLight->maxIntensitivityRatio += randRange(-0.006, 0.0075);
	efLight->maxIntensitivityRatio = clamp(efLight->maxIntensitivityRatio, 0.85f, 0.985f);
	
}
