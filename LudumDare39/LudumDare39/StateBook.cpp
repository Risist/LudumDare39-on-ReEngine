#include "StateBook.h"
#include "StateGame.h"
#include "StateMenu.h"


StateBook::StateBook(int _day)
	: day(_day)
{
}

void StateBook::onStart()
{
	tale.openFromFile("..\\..\\Resources\\Audio\\introTale.wav");
	tale.setPitch(0.95);
	tale.setVolume(40);
	tale.play();

	Gui::gui.add(new Gui::Button("gui_tutorialBook.txt"));

	if (day == 1)
	{
		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setStr("April 1st")->setPos(Vector2D(375, 100))->setSize(30);

		/// story
		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setPos(Vector2D(1200, 150))->setStr(
			"It was a long time ago...\n"
			"I still slightly remember that\n"
			"don\'t want but i do\n"
			"We came to the forest\n"
			"Somehow it became soo dark\n"
			"I felt soo cold inside\n"
			"The fire was our only hope...\n"
		);

		/// tutorial
		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setPos(Vector2D(1375, 300))->setStr(
			"Press E key while\n"
			" pointing mouse onto woods\n"
			" to collect one\n"
			"\n"
			"While holding woods\n"
			" near to the campfire\n"
			" prees again E key\n"
			" to throw them to the fire"
		);
	}
	else if (day == 2)
	{
		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setStr("April 2nd")->setPos(Vector2D(375, 100))->setSize(30);

		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setPos(Vector2D(1225, 150))->setStr(
			"We\'re here just a few days\n"
			"but I can\'t loose bad feelings\n"
			"about the place.\n"
			"Something hides in the woods,\n"
			"I know it!\n"
			"With flaming power\n"
			"I've found we\'re safe.\n"
			"Don\'t know for how long.\n"
		);

		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setPos(Vector2D(1100, 300))->setStr(
			"Darkness is dangerous\n"
			"try to avoid that on all costs\n"
			"\n"
			"Press Q key to throw\n"
			"a fireball from campfire\n"
		);
	}
	else if (day == 3)
	{
		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setStr("April 3th")->setPos(Vector2D(375, 100))->setSize(30);

		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setPos(Vector2D(810, 150))->setStr(
			"The night will never end!\n"
			"My hope is almost lost\n"
			"Friends ...\n"
			"Or people who used to be\n"
			"Are they mad?\n"
			"Am I ???\n"
		);

		/*
		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setPos(Vector2D(1100, 300))->setStr(
			"Be carefull, allies can become mad\n"
			"Then you have to kill them\n"
			"\n"
			"Press Q key to throw\n"
			"a fireball from campfire\n"
		);*/
	}
	else
	{
		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setStr("Night has gone!")->setPos(Vector2D(375, 100))->setSize(30);
		
		Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(Vector2D(350, 200))
			->setName("Play day 1")->setEvent([=]() { Game::stateManager.setState(new StateGame(1)); });

		Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(Vector2D(350, 300))
			->setName("Play day 2")->setEvent([=]() { Game::stateManager.setState(new StateGame(2)); });

		Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(Vector2D(350, 400))
			->setName("Play day 3")->setEvent([=]() { Game::stateManager.setState(new StateGame(3)); });

		
		Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setPos(Vector2D(975, 250))->setStr("   Congratulations from\n\n"
			"Maciej \'Risist\' Dominiak\n\n"
			"Marcin \'LiLatee\' Hradowicz");
	}

	if(day < 4) auto startGame = Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(Vector2D(700,600))
		->setName("Play")->setEvent([=]() { Game::stateManager.setState(new StateGame(day) ); });

	auto back = Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(Vector2D(350, 600))
		->setName("Back to menu")->setEvent([]() { Game::stateManager.setState(new StateMenu); });
}

Game::State * StateBook::onUpdate(sf::Time dt)
{
	wnd.clear(Color()); 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		return new StateBook;
	return nullptr;
}

void StateBook::onExit()
{
	Gui::gui.clear();
	if (tale.getStatus() == Music::Playing)
		tale.stop();
}