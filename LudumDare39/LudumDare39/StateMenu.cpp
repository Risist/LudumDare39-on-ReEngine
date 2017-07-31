#include "StateMenu.h"
#include "StateGame.h"
#include "StateCredits.h"
#include "StateBook.h"

StateMenu::StateMenu()
{
}

void StateMenu::onStart()
{
	/// position of gui element
	Vector2D pos (550,100);
	float offsetY = 60;  

	Gui::gui.add(new Gui::Text("gui_text.txt"))->setPos(pos + Vector2D(-20, 0))
		->setSize(25)->setStr("  Ludum Dare 39 - Game"); pos.y += 200;

	auto startGame = Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(pos)
		->setName("Start Game"); pos.y += offsetY;

	auto credits = Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(pos)
		->setName("Credits"); pos.y += offsetY*5;

	auto exit = Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(pos)
		->setName("Exit"); pos.y += offsetY;


	startGame->setEvent([]() { Game::stateManager.setState(new StateBook); });
	credits->setEvent([]() { Game::stateManager.setState(new StateCredits); });
	exit->setEvent([]() { wnd.close(); });

}

Game::State * StateMenu::onUpdate(sf::Time dt)
{
	wnd.clear(Color());
	return nullptr;
}

void StateMenu::onExit()
{
	Gui::gui.clear();
}


