#include "ActorBrushwood.h"
#include "Player.h"


ActorBrushwood::ActorBrushwood()
{
}

void ActorBrushwood::onInit()
{
	Actor::onInit();

	efModel = addEfect(new Efect::Model(6));
	efModel->model.color = Color_f(randRange(100, 155), randRange(100, 155), randRange(100, 155), 200);

}

void ActorBrushwood::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);

	static const float actionDistance = 125;
	if (actionMap.isActive("fire3"))
	{
		Vector2D facing = Vector2D(0, 1).getRotated(Player::player->getRotation());
		Vector2D toPlayer = (Player::player->getPosition() - getPosition()).getNormalised();
		float dot = facing.dot(toPlayer);
		if (dot > 0.6 && Player::player->readyToUse && collect(Player::player, Player::player->efMovement, Player::player->efModel->modelsUpdate[4]))
			Player::player->readyToUse = false;



		//if (((Vector2D)cam.mapPixelToCoords(Mouse::getPosition(wnd)) -getPosition())
			//.getLenghtSq() < actionDistance*actionDistance)
			//collect(Player::player, Player::player->efMovement, Player::player->efModel->modelsUpdate[4]);
	}
}

bool ActorBrushwood::collect(Game::Actor * collector, Efect::MovementAim * efMovement, Graphics::Model * handBurshwood)
{
	static const float actionDistance = 225.f;

	if ((collector->getPosition() - getPosition()).getLenghtSq() > actionDistance*actionDistance)
		return false;
	//cout << (collector->getPosition() - getPosition()).getLenght() << "\n";

	if (handBurshwood->color.a != 0)
		return false;

	handBurshwood->color = efModel->model.color;

	efMovement->reset();
	efMovement->efRotDir->direction = Vector2D(getPosition() - collector->getPosition()).angle();

	setAlive(false);
	
	return true;
}

