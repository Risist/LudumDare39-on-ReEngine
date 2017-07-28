#pragma once
#include <Re\Game\Efect\Movement\Agent\EfectMovementAimModificator.h>

namespace Game
{
	class Actor;
}

namespace Efect
{
	/// Movement efect which makes agent follow another game object
	/// @requires to work MovementAim added before
	class MovementFollow : public MovementAimModificator
	{
	public:
		MovementFollow() {}
		MovementFollow(Game::Actor* aim, float32 priority = 1.f );
		MovementFollow(Game::Actor* aim, MovementAim* movement, float32 priority = 1.f);

		void onUpdate(sf::Time dt) override;

		/*enum Direction : bool
		{
			into, ///< owner moves towards target
			out, ///< owner flees from target
		}direction{into};
		*/

		/// specifies distance to aim in which this agent will be trying to stay
		/// negative value means no boundurary (max - will be ok with staying in radius )
		float32 requiredDistanceMax{-1.f}; //< maximum distance in which agent wants to stay
		float32 requiredDistanceMin{-1.f}; //< minimal distance in which agent wants to stay

		MovementFollow* setDistance(float32 min, float32 max)
		{
			requiredDistanceMax = max;
			requiredDistanceMin = min;
			return this;
		}

		/// aim to follow
		/// if not set up efect will do nothing
		Game::Actor* aim{nullptr};
	};
}