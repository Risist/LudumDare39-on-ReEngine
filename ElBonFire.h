#pragma once
#include "GameWorld.h"
#include "efects.h"

namespace El
{
	class BonFire : public Game::Object
	{
	public:
		BonFire();

		void onInit() override;
		void onUpdate( float dt) override;

		EfectModel *efModel;
		EfectLightSource *efLight;
	};

}