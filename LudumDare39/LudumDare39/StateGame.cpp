#include "StateGame.h"
#include "Layers.h"
#include "ActorBonfire.h"
#include "LightController.h"
#include "ActorPrayer.h"
#include "ActorBrushwood.h"
#include "StateBook.h"
#include "ActorBird.h"

int StateGame::day;
StateGame *StateGame::stateGame = nullptr;

void StateGame::onStart()
{
	stateGame = this;
	music.openFromFile("..\\..\\Resources\\Audio\\inn_wolf.wav");
	music.setPitch(0.95);
	music.setVolume(30);
	music.setLoop(true);
	music.play();

	introVoice.openFromFile("..\\..\\Resources\\Audio\\whenNight.wav");
	introVoice.setPitch(0.95);

	/// game settings
	initKeys();
	Game::Layers::init();

	/// camera settings
	cam.setScale(1.85f);
	cam.setAlpha(1.f);

	/// insert game objects

	ActorPrayer::n = 0;
	ActorBird::n = 0;
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
		addPrayer(Vector2D(0, randRange(250.f, 500.f)).getRotated(), randRange(Angle::zero, Angle::full));


	Game::world.addActor(new ActorBonfire, Game::Layers::obstacle);

	leftTimeBarLeft = Gui::gui.add(new Gui::ProgressBar("gui_leftTimeBarLeft.txt"));
	leftTimeBarRight = Gui::gui.add(new Gui::ProgressBar("gui_leftTimeBarRight.txt"));
	tTip = Gui::gui.add(new Gui::Text("gui_text.txt"))->setPos(Vector2D(550, 60));

	if (day > 0)
	{
		tips.push_back("Collect woods");
		tips.push_back("Throw Woods to bonfire");
		tips.push_back("Collect woods to lit bonfire");
		tips.push_back("Press E key to interact");
		tips.push_back("Press E key to interact");
		tips.push_back("Press E key to interact");
		tips.push_back("Press ESC... to escape ;)");
		tips.push_back("Click on the map to move");
		tips.push_back("Avoid darkness");
		tips.push_back("Wait to end of the night");
		tips.push_back("Keep fire lit");
		tips.push_back("Stay in light to heal");
		tips.push_back("Press P to restart the level");
		tips.push_back("You are able to replace woods");
		tips.push_back("While carring woods press E to drop it");
		if (day > 1)
		{
			tips.push_back("Press Q key to shoot a fireball");
			tips.push_back("Press Q key to shoot a fireball");
			tips.push_back("Press Q key to shoot a fireball");
			tips.push_back("The fire is your only hope!");
			tips.push_back("Defend your allies");
			tips.push_back("Avoid ravens");
			tips.push_back("Kill ravens");
			tips.push_back("Flame your enemys");
			tips.push_back("Don\'t waste the fire!");
			if (day > 3)
			{
				tips.push_back("Who\'s mad???");
				tips.push_back("Are you mad???");
				tips.push_back("Allies can become mad");
				tips.push_back("Just kill me, please!");
				tips.push_back("The night will never end");
			}
		}
	}
	tTip->clear() << tips[sqrt(randRange(0, 1))*tips.size()];

	///lightController.lastLightIntensitivitySq = 1;
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
		leftTimeBarLeft->setProgress(nextState.getElapsedTime().asSeconds() / 95.f);
		leftTimeBarRight->setProgress(nextState.getElapsedTime().asSeconds() / 95.f);

		if (atVoice == false && nextState.getElapsedTime() > sf::seconds(90))
		{
			introVoice.play();
			atVoice = true;
		}else if (atVoice && introVoice.getStatus() == Music::Status::Stopped)
		{
			return new StateBook(2);
		}
	}
	else 
	{
		float stateMaxTime = 30 * (2 + day);
		float stateCompletePercent = nextState.getElapsedTime().asSeconds() / stateMaxTime;
		leftTimeBarLeft->setProgress( stateCompletePercent);
		leftTimeBarRight->setProgress(stateCompletePercent);

		if (nextState.getElapsedTime() > sf::seconds(20) &&
			clockSpawn.getElapsedTime() > sf::seconds(randRange((15 + ActorBird::n)*(1-stateCompletePercent), 25 + 5 * ActorBird::n)))
		{
			if (ActorBird::n < 3)
			{
				addBird(Vector2D(0, randRange(1600.f, 2300.f)).getRotated(), randRange(Angle::zero, Angle::full));
				std::cout << "bird spawned " << ActorBird::n << std::endl;
			}
			clockSpawn.restart();
		}
		else if (day > 2)
		{
			if (nextState.getElapsedTime() > sf::seconds(20) &&
				clockSpawnMage.getElapsedTime() > sf::seconds(randRange((10 - 0.5*day + ActorPrayer::n)*(1 - stateCompletePercent), 15 + 1.5*ActorPrayer::n)))
			{
				if (ActorPrayer::n < 4)
					addPrayer(Vector2D(0, randRange(1500.f, 2000.f)).getRotated(), randRange(Angle::zero, Angle::full), true);
				clockSpawnMage.restart();
			}
		}

		if (nextState.getElapsedTime() > sf::seconds(stateMaxTime))
		{
			return new StateBook(day + 1);
		}
	}

	if (nextTip.getElapsedTime() > sf::seconds(randRange(7,8)) )
	{
		tTip->clear() << tips[sqrt(randRange(0, 1))*tips.size()];
		nextTip.restart();
	}

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

Game::Actor * StateGame::addPrayer(const Vector2D & position, Angle rotation, bool agressive)
{
	auto player = Game::world.addActor(new ActorPrayer(agressive), Game::Layers::character);
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

Game::Actor * StateGame::addBird(const Vector2D & position, Angle rotation)
{
	auto player = Game::world.addActor(new ActorBird(), Game::Layers::character);
	player->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());

	return player;
}
