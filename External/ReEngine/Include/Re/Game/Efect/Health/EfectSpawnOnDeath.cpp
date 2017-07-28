#include <Re\Game\Efect\Health\EfectSpawnOnDeath.h>
#include <Re\Game\GameWorld.h>

namespace Efect
{
	SpawnOnDeath::SpawnOnDeath(function<Game::Actor*()> _createActor)
		:createActor(_createActor)
	{
	}
	bool SpawnOnDeath::onDeath(sf::Time dt)
	{
		auto actor = createActor();
		if (actor == nullptr)
			return true;

		Game::world.addActor(actor, getLayer());

		/// physics pos control
		if (actor->isRigidbodyCreated())
			actor->getRigidbody().SetTransform(
				  
				actor->getRigidbody().GetPosition()
				+ offset.getRotated(angle + getOwner()->getRotation())*toB2Position
				+ (Vector2D)getOwner()->getPosition()*toB2Position
				,
				actor->getRigidbody().GetAngle()
				+ getOwner()->getRotation().asRadian()
			);
		else
		/// transform pos control
		{
			actor->move(offset.getRotated(angle + getOwner()->getRotation())
				+ getOwner()->getPosition());
			actor->rotate(getOwner()->getRotation().asDegree());
		}

		return true;
	}
}