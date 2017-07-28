#include <Re\Game\Efect\Physics\EfectJoint.h>

namespace Efect
{

	RevoluteJoint::RevoluteJoint(Game::Actor* actorB)
	{
		assert(actorB->isRigidbodyCreated());
		def.bodyB = &actorB->getRigidbody();
		def.collideConnected = false;
		def.enableLimit = false;
		def.enableMotor = false;
	}

	void RevoluteJoint::onInit()
	{
		assert(getOwner()->isRigidbodyCreated());
		def.bodyA = &getOwner()->getRigidbody();
	}

	void RevoluteJoint::onStart()
	{
		joint = (b2RevoluteJoint*)Game::world.physicalWorld.CreateJoint(&def);
	}
}