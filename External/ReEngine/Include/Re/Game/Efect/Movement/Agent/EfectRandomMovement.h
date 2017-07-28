#pragma once
#include <Re\Game\Efect\Movement\Agent\EfectMovementAimModificator.h>

namespace Efect
{
	/// efect which will set up MovementAim destination
	/// finds random aim in circle offseted from owner
	class RandomMovement : public MovementAimModificator
	{
	public:
		RandomMovement(MovementAim*movement = nullptr, float32 priority = 1);

		void onUpdate(sf::Time dt) override;


		/// setters for easier initialization notation

		RandomMovement* setRadius(float32 min =  0, float32 max = 100)
		{
			radiusMin = min;
			radiusMax = max;
			return this;
		}
		RandomMovement* setTime(sf::Time min = sf::seconds(0), sf::Time max = sf::seconds(1))
		{
			tChangeAimMin = min;
			tChangeAimMax = max;
			return this;
		}
		RandomMovement* setOffset(const Vector2D& newOffset = Vector2D() )
		{
			offset = newOffset;
			return this;
		}

		/// data

		/// data to specify radius in which to find new aim
		float32		radiusMin{ 0.f }, 
					radiusMax{ 100.f };
		/// data to specify how long to wait for a new aim selection
		sf::Time	tChangeAimMin{ sf::seconds(0.f) },
					tChangeAimMax{ sf::seconds(1.f) };

		Vector2D	offset;

	protected:
		Clock clock;
		Vector2D destination;

		sf::Time tChangeAim;

		void newAim();
	};
}