#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\ResourceManager.h>

namespace Efect 
{
	class Particle;
}


/// wrapper class to simplify creation of particle emitters
class Emitter
{
public:
	Emitter();

	Emitter& 	setEmissionRate(float particlesPerSecond)
	{
		emitter.setEmissionRate(particlesPerSecond);
		return *this;
	}
	Emitter& 	setLifetime(thor::Distribution<sf::Time> particleLifetime)
	{
		emitter.setParticleLifetime(particleLifetime);
		return *this;
	}
	Emitter& 	setPosition(thor::Distribution<sf::Vector2f> particlePosition)
	{
		emitter.setParticlePosition(particlePosition);
		return *this;
	}
	Emitter& 	setVelocity(thor::Distribution<sf::Vector2f> particleVelocity)
	{
		emitter.setParticleVelocity(particleVelocity);
		return *this;
	}
	Emitter& 	setRotation(thor::Distribution<float> particleRotation)
	{
		emitter.setParticleRotation(particleRotation);
		return *this;
	}
	Emitter& 	setRotationSpeed(thor::Distribution<float> particleRotationSpeed)
	{
		emitter.setParticleRotationSpeed(particleRotationSpeed);
		return *this;
	}
	Emitter& 	setScale(thor::Distribution<sf::Vector2f> particleScale)
	{
		emitter.setParticleScale(particleScale);
		return *this;
	}
	Emitter& 	setColor(thor::Distribution<sf::Color> particleColor)
	{
		emitter.setParticleColor(particleColor);
		return *this;
	}
	Emitter& 	setTextureIndex(thor::Distribution<unsigned int> particleTextureIndex)
	{
		emitter.setParticleTextureIndex(particleTextureIndex);
		return *this;
	}


	friend Efect::Particle;
private:
	thor::UniversalEmitter emitter;
};

namespace Efect
{

	class Particle : public Base
	{
	public:
		Particle();

		void onUpdate(sf::Time dt) override;

		///	functions designed to setUp particle system
		/// usage goes like that
		/// actor.addEfect( new Efect::Particle).someFunction(args).anotherFunction(args) ect.

		// sets texture to use as graphics of particles
		// TODO when atlases will be implemented include possiblity to use set of different particles 
		Particle* setTexture(sf::Texture& ts)
		{ 
			particleSystem.setTexture(ts); 
			return this;
		}
		Particle* setTexture(ResId id)
		{ 
			//particleSystem.setTexture(tsInst[id]); 
			return this;
		}
		
		// adds function which can modify particles at runtime
		Particle* addAffector(std::function<void(thor::Particle&, sf::Time dt)> affector)
		{ 
			particleSystem.addAffector(affector);
			return this;
		}
		
		Particle* addEmitter(const Emitter& emitter) 
		{
			particleSystem.addEmitter(emitter.emitter); 
			return this;
		}

	private:
		thor::ParticleSystem particleSystem;
	};


}