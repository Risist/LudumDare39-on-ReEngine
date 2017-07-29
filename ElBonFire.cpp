#include "ElBonFire.h"

namespace El
{
	BonFire::BonFire()
	{
	}

	void BonFire::onInit()
	{
		Game::Object::onInit();
		loadTsPack(Bonfire);
		loadModel("model_bonFire.txt", "Bonfire");
		addEfect( new EfectParticle( "particle_bonfire.txt", "Bonfire",100, 1, 1, 0, nullptr, &efModel->model));
		////addEfect(new EfectLightSource( 50, 0.001, 1));
		addEfect(efLight = new EfectLightSource(50, 0.0003, 1));
	}

	void BonFire::onUpdate(float dt)
	{
		Game::Object::onUpdate(dt);

		/*efLight->fullLightDistance += randRange(-20, 20);
		efLight->fullLightDistance = clamp(efLight->fullLightDistance, 0.f, 150.f);*/
		//efLight->maxIntensitivityRatio = randRange(0, 1);

		efLight->maxIntensitivityRatio+= randRange(-0.006, 0.0075);
		efLight->maxIntensitivityRatio= clamp(efLight->maxIntensitivityRatio, 0.f, 1.f);
	}
}