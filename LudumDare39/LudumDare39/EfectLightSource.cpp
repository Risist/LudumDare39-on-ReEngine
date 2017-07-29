#include "EfectLightSource.h"
#include "LightController.h"

EfectLightSource::EfectLightSource(float _fullLightDistance, float _intensitivityFall, float _maxIntensitivityRatio)
	: fullLightDistance(_fullLightDistance), intensitivityFall(_intensitivityFall), maxIntensitivityRatio(_maxIntensitivityRatio)
{
}


void EfectLightSource::onInit()
{
	Base::onInit();
}

void EfectLightSource::onUpdate(sf::Time dt)
{
	Base::onUpdate(dt);

	lightController.checkLightSource(getOwner(), fullLightDistance, intensitivityFall, maxIntensitivityRatio);
}

