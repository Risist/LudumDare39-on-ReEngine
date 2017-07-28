#pragma once
#include <Re\Game\Efect\MultiEfect.h>
namespace Graphics
{
	class ModelDef;
}

namespace Game
{
	/// Base class for all objects within the scene
	/// Has many events what can be overrided;
	/// Create actors only by createActor function of Game::World
	/// Constructor is not called; use onInit or/and onRestart instead
	/// deconstructor as well; use onDeath instead
	class Actor : public sf::Transformable, public Efect::Multi
	{
	public:
		Actor();
		virtual ~Actor();

		//// Events

		/// in onInit initiate all heavy parametrs
		/// like models, colliders ect
		/// that are constant to every Actor of the class
		virtual void onInit() override;

		/// event called every frame
		/// dt is the time elapsed from last update
		virtual void onUpdate(sf::Time dt) override;

		/// check whether or not the Actor is still alive
		/// used mostly by Game::World to decide which one 
		/// from onDeath and onUpdate should be called
		bool isAlive() const
		{
			return !readyToRemove;
		}
		void setAlive(bool s)
		{
			readyToRemove = !s;
		}
		/// update-like event called after death of an object
		/// di is the time elapsed from last update
		/// returns whether the object can be destroyed
		virtual bool onDeath(sf::Time dt) override;


		/// When the object collides with other those events are send
		/// taken actor is the other one with collision appeared
		/// contact is all collision data sended by box2d ( for more info look into box2d documentation )
		/// events wont be called until the Actor hasn't rigidbody created ( use createRigidbody function)
		virtual void onCollisionEnter(Actor& otherActor, b2Contact& contact) override;
		virtual void onCollisionExit(Actor& otherActor, b2Contact& contact) override;

		/// define custom filtering to the object
		virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture) override;

	public:
		/// creates rigidbody of the actor ( for more info look into box2d documentation)
		void createRigidbody(const b2BodyDef& def);
		/// returns rigidbody assigned to the Actor
		/// @Warring call this function only if you are sure body has been created
		b2Body& getRigidbody() { assert(isRigidbodyCreated()); return *rigidbody; }
		const b2Body& getRigidbody() const { assert(isRigidbodyCreated()); return *rigidbody; }
		bool isRigidbodyCreated() const { return rigidbody != nullptr; }
		void destroyRigidbody();

	public:

		/// update transform of rigidbody to fit into Actors transform
		/// @Warring call this only when rigidbody is created
		void updateRigidbody(const Vector2D& originOffset = Vector2D(0, 0));

		/// update transform of Actor to fit into rigidbodys transform
		/// @Warring call this only when rigidbody is created
		void updateTransform(const Vector2D& originOffset = Vector2D(0, 0));

		/// updates taken as an argument transformable object to fit into actor's transform
		void updateGraphics(Transformable& transformable);
		void updateGraphics(Graphics::ModelDef& modelDef);

	public:
		/// overrided operators
		__forceinline Vector2D getPosition() const { return Transformable::getPosition(); }
		__forceinline Angle getRotation() const { return Degree(Transformable::getRotation()); }
		__forceinline Vector2D getScale() const { return Transformable::getScale(); }

		void setActive(bool s);
		bool isActive() { return activated; }

	protected:

		friend class World;

		/// rigidbody used by the actor. To get any collision events you need to have it filled;
		b2Body *rigidbody;

	private:
		/// actor has no owner ( in terms of efect)
		using Efect::Multi::setOwner;
		using Efect::Multi::getOwner;

		/// use set/is Active instead;
		using Efect::Base::activated;
	};

}