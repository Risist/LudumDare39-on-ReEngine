#pragma once
#include <Re\Game\Efect\Movement\EfectRotateToDirection.h>

namespace Efect
{

	class RadiusMovement : public Base
	{
	public:
		RadiusMovement(
			float32 movementSpeed,
			float32 rotationRadius = 100,
			float32 movementRadius = 150,
			float32 movementRadiusMax = 400
		);
		RadiusMovement(
			float32 movementSpeed,
			RotateToDirection *efRotDir,
			float32 rotationRadius = 100,
			float32 movementRadius = 150,
			float32 movementRadiusMax = 400
		);

		void onInit() override;
		void onUpdate(sf::Time dt) override;

		
		float32 movementSpeed;

		/// the efect does sevral actions
		/// each one runs only when mouse is in sertain distance from character (center of screan)
		float32 rotationRadius; /// in radius > rotationRadius character rotates towards mouse
		float32 movementRadius; /// in radius > movementRadius character starts to move towards mouse
		float32 movementRadiusMax; /// describes in which radius character will accerelate with max speed


		/// pointner to efect which will change direction of owner
		/// nullptr disables the this feature
		RotateToDirection *efRotDir{ nullptr };


		float32 lastSpeedModificator{0};
	};

}