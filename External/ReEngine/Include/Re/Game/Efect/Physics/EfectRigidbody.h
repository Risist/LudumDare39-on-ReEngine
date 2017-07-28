#pragma once

#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{
	/// efect creates rigidbody and after that removes self
	class Rigidbody : public Base
	{
	public:
		/// create static Rigidbody
		Rigidbody();
		/// Dynamic & kinematic
		Rigidbody(float32 linearDamping, float32 angularDamping,
			bool fixedRotation = false, bool bullet = false, bool allowSleep = true,
			b2BodyType type = b2_dynamicBody);

		void onInit() override;

		b2BodyDef def;
	};


}