#include "LightController.h"

LightController lightControler(nullptr, 0.075, 1);

LightController::LightController(Game::Object *_observer, float _minimalLight, float _maximalLight)
	: observer(_observer), minimalLight(_minimalLight), maximalLight(_maximalLight)
{
}

void LightController::update(Camera& cam)
{
	// set new darkness level
	cam.setDarkness(
		clamp(
			pow(	bestLightIntensitivitySq, 8.f )
	
		, minimalLight, maximalLight)
		);

	// reset Light intensitivity
	bestLightIntensitivitySq = minimalLight * minimalLight;
}


void LightController::checkLightSource(Game::Object *source, float fullLightDistance, float intensitivityFall, float maxIntensitivityRatio)
{
	// vialidance check
	if (observer == nullptr || source == nullptr)
		return;

	float distanceSq = (observer->getPos().position - source->getPos().position).getLenghtSq();

	if (fullLightDistance * fullLightDistance > distanceSq) 
		// in full light range
		checkLightSource(maximalLight*maximalLight*maxIntensitivityRatio *maxIntensitivityRatio);
	else
		// with changing light power
		checkLightSource(
		
		(maximalLight*maximalLight - (distanceSq - fullLightDistance*fullLightDistance) * intensitivityFall * intensitivityFall )
				*maxIntensitivityRatio *maxIntensitivityRatio
		);
}
