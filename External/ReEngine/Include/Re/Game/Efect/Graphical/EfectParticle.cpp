#include <Re\Game\Efect\Graphical\EfectParticle.h>
#include <Re\Graphics\Camera.h>
namespace Efect
{
	Particle::Particle()
	{
	}

	void Particle::onUpdate(sf::Time dt)
	{
		particleSystem.update(dt);
		cam.draw(particleSystem);
	}



}

Emitter::Emitter()
{
	emitter.setEmissionRate(50);
	emitter.setParticleLifetime(sf::seconds(1));
}