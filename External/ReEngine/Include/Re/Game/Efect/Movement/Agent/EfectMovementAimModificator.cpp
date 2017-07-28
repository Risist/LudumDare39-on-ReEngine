#include <Re\Game\Efect\Movement\Agent\EfectMovementAimModificator.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	void MovementAimModificator::onInit()
	{
		// if perously not setted up find movement efect
		if (movement == nullptr)
		{
			movement = getOwner()->getEfect<MovementAim>();
		}
	}
}