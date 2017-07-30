#include "EfectLightSource.h"
#include "LightController.h"

EfectLightSource::EfectLightSource( float _fullLightDistance, float _intensitivityFall, float _maxIntensitivityRatio)
	: fullLightDistance(_fullLightDistance), intensitivityFall(_intensitivityFall), maxIntensitivityRatio(_maxIntensitivityRatio)
{
}


void EfectLightSource::onInit()
{
	Efect::onInit();
}

void EfectLightSource::onUpdate(sf::Time dt)
{
	Efect::onUpdate(dt);

	lightControler.checkLightSource(getOwner(), fullLightDistance, intensitivityFall, maxIntensitivityRatio);
}
