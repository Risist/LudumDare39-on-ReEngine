#include "StateGame.h"
#include "Layers.h"
#include "ActorBonfire.h"
#include "LightController.h"

void StateGame::onStart()
{
	/// game settings
	initKeys();
	Game::Layers::init();

	/// camera settings
	cam.setScale(1.85f);
	cam.setAlpha(1.f);

	/// insert game objects
	addBackground(Vector2D());
	auto player = Game::world.addActor(new Player(), Game::Layers::character);
	lightController.observer = player;

	for (int i = 0; i < 50; ++i)
		addObstacle(Vector2D(0, randRange(100.f, 5500.f)).getRotated(), randRange(Angle::zero, Angle::full) );

	Game::world.addActor(new ActorBonfire, Game::Layers::obstacle);
}

Game::State * StateGame::onUpdate(sf::Time dt)
{
	sf::Sprite s(sf::Texture());

	Game::world.onUpdate(dt);
	cam.display(wnd);
	
	lightController.update(cam);

	if (actionMap.isActive("restart"))
		return new StateGame;
	return nullptr;
}

void StateGame::onExit()
{
	Gui::gui.clear();
	Game::world.clear();
}

void StateGame::initKeys()
{
	/// movement
	actionMap["up"] = thor::Action(sf::Keyboard::W);
	actionMap["down"] = thor::Action(sf::Keyboard::S);
	actionMap["left"] = thor::Action(sf::Keyboard::A);
	actionMap["right"] = thor::Action(sf::Keyboard::D);

	/// actions and skills
	actionMap["fire1"] =
		thor::Action(sf::Mouse::Left) || thor::Action(sf::Mouse::Right) 
		|| thor::Action(thor::JoystickButton(0, 5), thor::Action::PressOnce);
	
	actionMap["fire2"] = thor::Action(sf::Keyboard::Q, thor::Action::PressOnce);
	actionMap["fire3"] = thor::Action(sf::Keyboard::E, thor::Action::PressOnce);

	/// helper
	actionMap["debugPhysics"] = thor::Action(sf::Keyboard::Z, thor::Action::Hold);
	actionMap["restart"] = thor::Action(sf::Keyboard::P, thor::Action::PressOnce);
}

///////////////////////////////////////////////////////////
Game::Actor * StateGame::addPlayer(const Vector2D & position, Angle rotation)
{
	auto player = Game::world.addActor(new Player(), Game::Layers::character);
	player->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());

	return player;
}

Game::Actor * StateGame::addBackground(const Vector2D & position)
{
	auto background = Game::world.addActor(new Game::Actor, Game::Layers::background);

	background->setPosition(position);

	auto efModel = background->addEfect(new Efect::Model((ResId)2))
		->setScale(Vector2D(1.f, 1.f));
	return background;
}

Game::Actor * StateGame::addObstacle(const Vector2D & position, Angle rotation)
{
	Game::Actor *actor = Game::world.addActor(new Game::Actor,Game::Layers::obstacle);
	actor->addEfect(new Efect::Rigidbody());
	actor->addEfect(new Efect::ColliderBox(Vector2D(75, 75), 10));
	actor->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());


	actor->addEfect(new Efect::UpdateTransform());
	actor->addEfect(new Efect::GraphicsRect(Vector2D(150, 150), Color(100, 100, 100, 150)));

	return actor;
}
