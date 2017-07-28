#include <Re\Game\GameActor.h>
#include <Re\Game\GameWorld.h>
#include <Re\Graphics\Model\GraphicsModelDef.h>

namespace Game
{
	Actor::Actor()
	{
		setAlive(true);
		rigidbody = nullptr;

		/// Actor has no owner
		setOwner(this);
	}

	Actor::~Actor()
	{
		if (rigidbody)
		{
			destroyRigidbody();
		}
	}

	void Actor::onInit()
	{
		Efect::Multi::onInit();
	}
	void Actor::onUpdate(sf::Time dt)
	{
		Efect::Multi::onUpdate(dt);
	}

	bool Actor::onDeath(sf::Time dt)
	{
		return Efect::Multi::onDeath(dt);
	}

	void Actor::onCollisionEnter(Actor & otherActor, b2Contact & contact)
	{
		Efect::Multi::onCollisionEnter(otherActor, contact);
	}

	void Actor::onCollisionExit(Actor & otherActor, b2Contact & contact)
	{
		Efect::Multi::onCollisionExit(otherActor, contact);
	}

	bool Actor::shouldCollide(b2Fixture * myFixture, b2Fixture * otherFixture)
	{
		return Efect::Multi::shouldCollide(myFixture, otherFixture);
	}

	void Actor::createRigidbody(const b2BodyDef &def)
	{
		rigidbody = world.physicalWorld.CreateBody(&def);
		rigidbody->SetUserData(this);
	}

	void Actor::destroyRigidbody()
	{
		rigidbody->GetWorld()->DestroyBody(rigidbody);
		rigidbody->SetUserData(nullptr);
		rigidbody = nullptr;
	}



	void Actor::updateRigidbody(const Vector2D & originOffset)
	{
		assert(isRigidbodyCreated());

		//// update without interpolation
		//// TODO make define which will be able to turn off/on interpolation
		/// update rigidbody transform
		rigidbody->SetTransform(getPosition()* toB2Position,
			getRotation().asRadian());
	}

	void Actor::updateTransform(const Vector2D & originOffset)
	{
		assert(isRigidbodyCreated());

		Transformable::setPosition((Vector2D)rigidbody->GetPosition() * toSfPosition);
		Transformable::setRotation(Radian(rigidbody->GetAngle()).asDegree());

	}

	void Actor::updateGraphics(Transformable & transformable)
	{
		//transformable.setOrigin(transformable.getOrigin() + Transformable::getOrigin() );
		transformable.setPosition(Transformable::getPosition());
		transformable.setRotation(Transformable::getRotation());
		//transformable.setScale(Transformable::getScale() *(Vector2D)transformable.getScale());
	}

	void Actor::updateGraphics(Graphics::ModelDef & modelDef)
	{
		//modelDef.posNoRot = getPosition();
		//modelDef.rot = getRotation();
	}

	void Actor::setActive(bool s)
	{
		Efect::Base::activated = s;
		if (isRigidbodyCreated())
			getRigidbody().SetActive(s);
	}


}