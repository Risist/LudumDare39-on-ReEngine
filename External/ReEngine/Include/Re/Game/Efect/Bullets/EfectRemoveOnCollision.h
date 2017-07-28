#include <Re\Game\Efect\EfectBase.h>


namespace Efect
{

	class RemoveOnCollision : public Base
	{
	public:
		RemoveOnCollision() {}
		RemoveOnCollision(function<bool(Game::Actor& other, b2Contact&)> allowdedToDelete);

		void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact) override;

		function<bool(Game::Actor& other, b2Contact& )> allowdedToDelete{ [](Game::Actor&, b2Contact&) {return true; } };
	};

}