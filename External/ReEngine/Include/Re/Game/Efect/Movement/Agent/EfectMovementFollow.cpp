#include <Re\Game\Efect\Movement\Agent\EfectMovementFollow.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	MovementFollow::MovementFollow(Game::Actor * _aim, float32 priority)
		: MovementAimModificator(priority), aim(_aim)
	{
	}

	MovementFollow::MovementFollow(Game::Actor * _aim, MovementAim * _movement, float32 priority)
		: MovementAimModificator(priority, _movement),  aim(_aim)
	{
	}

	void MovementFollow::onUpdate(sf::Time dt)
	{
		assert(movement);
		/// check if aim is setted up
		if(aim == nullptr)
			return;
		
		Vector2D toAim = aim->getPosition() - getOwner()->getPosition();
		float32 distSq = toAim.getLenghtSq();
			
		if (distSq > requiredDistanceMax *requiredDistanceMax)
			movement->setDestination(aim->getPosition(), priority);
		else if (distSq < requiredDistanceMin * requiredDistanceMin)
			movement->setDestination((Vector2D)aim->getPosition() - toAim * 2, priority);
		else 
			movement->setDestination(getOwner()->getPosition(), priority);
	}

}