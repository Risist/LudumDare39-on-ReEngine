#include <Re\Game\Efect\Bullets\EfectRemoveAfterDelay.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	RemoveAfterDelay::RemoveAfterDelay(sf::Time _delay)
		:delay(_delay)
	{
	}
	void RemoveAfterDelay::onInit()
	{
		clock.restart();
	}
	void RemoveAfterDelay::onUpdate(sf::Time dt)
	{
		if (clock.getElapsedTime() > delay)
		{
			getOwner()->setAlive(false);
		}
	}
}