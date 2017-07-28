#include <Re\Game\Efect\Physics\EfectRigidbody.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	Rigidbody::Rigidbody()
	{
		///static
		def.type = b2_staticBody;
	}

	Rigidbody::Rigidbody(float32 linearDamping, float32 angularDamping, bool fixedRotation, bool bullet, bool allowSleep, b2BodyType type)
	{
		def.type = type;

		def.angularDamping = angularDamping;
		def.linearDamping = linearDamping;
		def.allowSleep = allowSleep;
		def.fixedRotation = fixedRotation;
		def.bullet = bullet;
	}

	void Rigidbody::onInit()
	{
		def.position.x = getOwner()->getPosition().x * toB2Position;
		def.position.y = getOwner()->getPosition().y * toB2Position;
		def.angle = getOwner()->getRotation().asRadian();

		getOwner()->createRigidbody(def);
		readyToRemove = true;
	}
}