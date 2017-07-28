#pragma once
#include <Re\Game\Efect\Movement\EfectMovementAim.h>

namespace Efect
{

	class MovementAimModificator : public Base
	{
	public:
		MovementAimModificator(float32 _priority = 1, MovementAim* _movement = nullptr) 
			: priority(_priority), movement(_movement)
		{}

		void onInit();

		
		float32 priority{ 1.f };
	protected:
		MovementAim *movement{nullptr};
	};

}