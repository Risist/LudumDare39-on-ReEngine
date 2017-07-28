#pragma once

#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{
	/// efect which invokes update of transform to fit rigidbody every frame
	/// there are sevral update modes
	/// @Warring before first update of this efect 
	///		Actor have to have an rigidbody created
	class UpdateTransform : public Base
	{
	public:
		enum Mode
		{
			none,
			toTransform,
			toRigidbody,
		} positionMode, rotationMode;
		UpdateTransform(Mode _positionMode, Mode _rotationMode);
		UpdateTransform(Mode _wholeMode= toRigidbody);

		void onUpdate(sf::Time dt) override;
	};

}