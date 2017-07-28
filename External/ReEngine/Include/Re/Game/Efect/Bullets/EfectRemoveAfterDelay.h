#pragma once

#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{

	class RemoveAfterDelay : public Base
	{
	public:
		RemoveAfterDelay(sf::Time delay);

		void onInit() override;
		void onUpdate(sf::Time dt) override;

		sf::Time delay;
	protected:
		sf::Clock clock;
	};


}