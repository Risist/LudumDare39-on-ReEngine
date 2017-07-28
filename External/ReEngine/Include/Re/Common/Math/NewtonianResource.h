#pragma once
#include <Re\Common\Settings.h>
#include <Re\Common\Scripts\ResScripts.h>

/// class that takes care over some value in newton-like fashion
/// Make sure the ptr to value is set by constructor (or while using malloc before any function depended on value)
/// because otherwise you will face an assert
template<typename T = float32, typename float_t = float32>
class NewtonianResource : public Res::ISerialisable
{
public:
	NewtonianResource(T* _value) 
		: value(_value),
		force(),
		velocity(),
		resetForce(),
		resetVelocity(),
		inverseMass()
	{
		assert(value != nullptr);
	}


	/// updates parametrs of the structure
	/// dt - time elapsed from last update taken as seconds
	void onUpdate(sf::Time dt)
	{
		assert(value != nullptr);
		velocity += force*inverseMass * dt.asSeconds();
		force *= resetForce;

		(*value) += velocity*dt;
		velocity *= resetVelocity;
	}

public:

	/// sets mass
	/// @Warring do not try to set 0 mass
	void setMass(float_t s)
	{
		assert(s != 0.f);
		inverseMass = 1/s;
	}
	/// returns actually holded mass
	/// do not try to call this when you have unchangable value (inverseMass == 0.f)
	float_t getMass()
	{
		assert(inverseMass != 0.f);
		return 1/inverseMass;
	}

	/// changes internal pointner to value
	/// @Warring do not try to assign to nullptr
	///		otherwise you will face an assert
	void setValuePtr(T* s) { assert(s != nullptr);  value = s; }

	/// get value holded by the class
	T& getValue() { assert(value != nullptr); return *value; }
	const T& getValue() const { assert(value != nullptr); return *value; }

	/// adds force
	void addForce(const T& add) { force += add; }
	/// returns actual force;
	const T& getForce() const { return force; }

	/// returns actual velocity;
	const T& getVelocity() const { return velocity; }

	/// sets reset velocity; argument have to be in range [0,1] inclusivelly - otherwise program will assert
	void setResetVelosity(const float_t& s) { assert(s >= 0.f && s <= 1.f); resetVelocity = s; }
	/// returns reset velocity;
	float_t getResetVelosity() const { return resetVelocity;  }


	/// sets reset force; argument have to be in range [0,1] inclusivelly - otherwise program will assert
	void setResetForce(const float_t& s) { assert(s >= 0.f && s <= 1.f); resetForce = s; }
	/// returns reset force; 
	float_t getResetForce() const { return resetForce; }

private:
	T* value;
	
	/// 
	T velocity, force;
	/// reset velocity/force works like dampting
	/// each frame makes accordingly velocity/force lesser; 
	/// the value should be in range [0,1] inclusivelly 
	/// where lover value means less velocity/force stays inside velocity/force
	float_t resetVelocity, resetForce;
	
	/// holds inverse mass
	/// makes forces less strong
	/// holding inverse mass has more sense because 0 inverse mass means unchangable value 
	/// whereas 0 mass is weird  
	float_t inverseMass;
protected:
	virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override
	{
		assert(value != nullptr);
		saver.save("position", (*value));
		saver.save("velocity", velocity);
		saver.save("force", force);

		saver.save("inverseMass", inverseMass);

		saver.save("resetVelocity", resetVelocity);
		saver.save("resetForce", resetForce);
	};
	virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
	{
		assert(value != nullptr);
		(*value) = loader.load("value", T());
		velocity = loader.load("velocity", T() );
		force = loader.load("force", T());

		inverseMass = loader.load("inverseMass", float_t() );

		resetVelocity = loader.load("resetVelocity", float_t());
		resetForce = loader.load("resetForce", float_t());
	}
};
