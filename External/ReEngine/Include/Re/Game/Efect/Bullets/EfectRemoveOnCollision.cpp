#include <Re\Game\Efect\Bullets\EfectRemoveOnCollision.h>
#include <Re\Game\GameActor.h>

namespace Efect
{


	RemoveOnCollision::RemoveOnCollision(function<bool(Game::Actor& other, b2Contact&)> _allowdedToDelete)
		: allowdedToDelete(_allowdedToDelete)
	{

	}
	void RemoveOnCollision::onCollisionEnter(Game::Actor & otherActor, b2Contact & contact)
	{
		if (allowdedToDelete(otherActor, contact))
		{
			getOwner()->setAlive(false);
		}
	}
}