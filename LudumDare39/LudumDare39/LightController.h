#pragma once
#include <Re\ReEngine.h>

class LightController
{
public:
	LightController(Game::Actor *observer = nullptr, float minimalLight = 0, float maximalLight = 1);



	void update(Camera& cam);


	void checkLightSource(float intensitivitySq)
	{
		bestLightIntensitivitySq = intensitivitySq > bestLightIntensitivitySq
			? intensitivitySq : bestLightIntensitivitySq;
	}
	// the far light source is from observer the darker is scene
	// if the distance is less than fullLightDistance then is used maximal available intensitivity
	// otherwise intensitivity becomes less the distance is bigger dependinglu on intensitivityFall parametr
	// at 0 intensitivityFall always max available is used
	// at 1 intensitivityFall light is seen only in fullLightDistance
	// last parametr : maxIntensitivityRatio changes power of light source
	// sould be in range of 0 to 1 includive
	void checkLightSource(Game::Actor *source, float fullLightDistance, float intensitivityFall, float maxIntensitivityRatio);

	Game::Actor *observer;
	// in which range can be light? 
	// most wide is from 0 to 1
	float minimalLight, maximalLight;

private:

	float bestLightIntensitivitySq;
};
extern LightController lightController;


