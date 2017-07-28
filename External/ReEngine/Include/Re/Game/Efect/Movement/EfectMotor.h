#pragma once
#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{

	class Motor : public Base
	{
	public:
		Motor(float32 movementSpeed, Angle angleOffset = Angle() );

		void onUpdate(sf::Time dt) override;

		float32 movementSpeed;
		Angle angleOffset;
	};

}
