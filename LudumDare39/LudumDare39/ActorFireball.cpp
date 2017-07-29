#include "ActorFireball.h"

ActorFireball::ActorFireball(Angle _direction)
	: direction(_direction)
{
}

void ActorFireball::onInit()
{
	Actor::onInit();

	addEfect(new Efect::Rigidbody(10,10));
	addEfect(new Efect::ColliderCircle(75.f));
	addEfect(new Efect::UpdateTransform());
	addEfect(new Efect::DamageOnCollision(5.));
	addEfect(new Efect::RemoveAfterDelay(sf::seconds(1.25f)));

	efLight = addEfect(new EfectLightSource(0, 0.000325, 0.95));
	addEfect(new Efect::Motor(250.f, direction));

	addEfect(new Efect::Particle())->addEmitter(
		Emitter().setEmissionRate(270).setLifetime([]() { return sf::seconds(randRange(0.1f, 0.4f)); })
			.setPosition([&](){
				particleAngle = randRange(Angle::zero, Angle::full);
				return getPosition() + Vector2D(randRange(10.f, 40.f), 0).getRotated(particleAngle); 
			})
			.setScale([]() { 
				float r = randRange(0.3f,0.7f);
				return Vector2D(r, r);
			})
			.setVelocity([&]() {	return Vector2D(randRange(10.f, 60.f), 0).getRotated(particleAngle); })
			.setRotation([](){		return randRange(0.f,360.f); })
			.setRotationSpeed([](){ return randRange(-10.5f,10.5f); })
			.setColor([]() {
				float d = randRange(0.5f, 1.2f);
				return Color(200*d, 180*d, 180*d, randRange(30, 40)); 
			})
	)->setTexture(ResId(401));

}

void ActorFireball::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt); 

	efLight->maxIntensitivityRatio += randRange(-0.006, 0.0075);
	efLight->maxIntensitivityRatio = clamp(efLight->maxIntensitivityRatio, 0.85f, 1.f);

}