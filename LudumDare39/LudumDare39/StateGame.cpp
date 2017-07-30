#include "StateGame.h"
#include "Layers.h"
#include "ActorBonfire.h"
#include "LightController.h"
#include "ActorPrayer.h"
#include "ActorBrushwood.h"
#include "StateBook.h"

int StateGame::day;

void StateGame::onStart()
{
	music.openFromFile("..\\..\\Resources\\Audio\\inn_wolf.wav");
	music.setPitch(0.95);
	music.setVolume(45);
	music.setLoop(true);
	music.play();

	introVoice.openFromFile("..\\..\\Resources\\Audio\\whenNight.wav");
	introVoice.setPitch(0.95);
	//introVoice.play();

	/// game settings
	initKeys();
	Game::Layers::init();

	/// camera settings
	cam.setScale(1.85f);
	cam.setAlpha(1.f);

	/// insert game objects

	ActorPrayer::n = 0;
	auto player = addPlayer(Vector2D(0, 200), Degree(180));
  
	lightController.observer = player;


	for (int i = 0; i < 25; ++i)
		addGrass(Vector2D(0, sqrt(randRange(0.f, 1.f))*2200 ).getRotated(), randRange(Angle::zero, Angle::full));

	{
		Game::world.addActor(new Game::Actor, Game::Layers::background)
			->addEfect(new Efect::Lambda)
			->_onUpdate = [](sf::Time) 
		{
			sf::Sprite s;
			s.setTexture(atlasInst[100]);
			s.setOrigin(s.getTextureRect().width / 2, s.getTextureRect().height / 2);
			s.setScale(1.25f, 1.25f);
			s.setColor(Color(180, 120, 120, 30));
			for (int i = 0; i < 10; ++i)
			{
				cam.draw(s);
				s.scale(0.999, 0.999f);
			}
		};
	}
	
	for (int i = 0; i < 50; ++i)
		addBurshwood(Vector2D(0, 750.f + sqrt(randRange(0, 1))*750.f).getRotated(), randRange(Angle::zero, Angle::full));

	for (int i = 0; i < 15; ++i)
		addObstacle(Vector2D(0, randRange(1150.f, 1500.f)).getRotated(), randRange(Angle::zero, Angle::full));


	for(int i = 0; i < 3; ++i)
		addPrayer(Vector2D(0, randRange(1000.f, 1500.f)).getRotated(), randRange(Angle::zero, Angle::full));


	Game::world.addActor(new ActorBonfire, Game::Layers::obstacle);
}

Game::State * StateGame::onUpdate(sf::Time dt)
{
	
	{
		sf::Sprite s;
		s.setTexture(atlasInst[207]);
		s.setOrigin(s.getTextureRect().width / 2, s.getTextureRect().height / 2);
		s.setScale(4, 4);
		s.setColor(Color(150, 150, 150));

		for (int i = -5; i < 5; i++) {
			s.scale(-1, 1);

			for (int j = -5; j < 5; j++) {
				s.setPosition(i * s.getTextureRect().width*abs(s.getScale().x), j * s.getTextureRect().height *abs(s.getScale().y) );
				s.scale(1, -1);
				cam.draw(s);
			}
		}
	}
	

	
	if (day == 1 )
	{
		
		if (atVoice == false && nextState.getElapsedTime() > sf::seconds(15*4))
		{
			introVoice.play();
			atVoice = true;
		}else if (atVoice && introVoice.getStatus() == Music::Status::Stopped)
		{
			return new StateBook(2);
		}
	}
	/*if (ActorPrayer::n < 10 && clockSpawn.getElapsedTime() > sf::seconds(randRange(2*ActorPrayer::n*ActorPrayer::n,3*ActorPrayer::n*ActorPrayer::n) ))
	{
		addPrayer(Vector2D(0, randRange(1400.f, 1700.f)).getRotated(), randRange(Angle::zero, Angle::full));
		clockSpawn.restart();
		//cout << ActorPrayer::n << '\n';
	}*/

	Game::world.onUpdate(dt);
	cam.display(wnd);
	
	lightController.update(cam);

	if (actionMap.isActive("restart"))
		return new StateGame(day);
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
	actionMap["fire3"] = thor::Action(sf::Keyboard::E, thor::Action::Hold);

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
	actor->addEfect(new Efect::ColliderCircle(100.f));
	actor->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());
	actor->setPosition(position);
	actor->setRotation(rotation.asDegree());

	actor->addEfect(new Efect::Model(5));
	return actor;
}

Game::Actor * StateGame::addPrayer(const Vector2D & position, Angle rotation)
{
	auto player = Game::world.addActor(new ActorPrayer(), Game::Layers::character);
	player->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());

	return player;
}

Game::Actor * StateGame::addBurshwood(const Vector2D & position, Angle rotation)
{
	Game::Actor *actor = Game::world.addActor(new ActorBrushwood, Game::Layers::background);
	//actor->addEfect(new Efect::Rigidbody());
	//actor->addEfect(new Efect::ColliderCircle(100.f));
	//actor->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());
	actor->setPosition(position);
	actor->setRotation(rotation.asDegree());
	return actor;
}
Game::Actor * StateGame::addGrass(const Vector2D & position, Angle rotation)
{
	Game::Actor *actor = Game::world.addActor(new Game::Actor, Game::Layers::background);
	//actor->addEfect(new Efect::Rigidbody());
	//actor->addEfect(new Efect::ColliderCircle(100.f));
	//actor->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());
	actor->setPosition(position);
	actor->setRotation(rotation.asDegree());

	actor->addEfect(new Efect::Model(7))->model.color = Color_f(randRange(100, 140), randRange(100, 140), randRange(100, 140), randRange(180, 240));
	return actor;
}
