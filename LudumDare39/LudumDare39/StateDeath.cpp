#include "StateDeath.h"
#include "StateMenu.h"
#include "StateGame.h"


StateDeath::StateDeath()
{
}

void StateDeath::onStart()
{
	Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setStr("You\'re dead!")->setPos(Vector2D(550, 200))->setSize(60);
	Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setStr("it\'s day:")->setPos(Vector2D(550, 300))->setSize(40);
	Gui::gui.add(new Gui::Text("gui_bookText.txt"))->setStr(StateGame::day)->setPos(Vector2D(525, 350))->setSize(35);

	auto startGame = Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(Vector2D(700, 550))
		->setName("Try again")->setEvent([=]() { Game::stateManager.setState(new StateGame(StateGame::day)); });

	auto back = Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(Vector2D(350, 550))
		->setName("Back to menu")->setEvent([]() { Game::stateManager.setState(new StateMenu); });

}

Game::State * StateDeath::onUpdate(sf::Time dt)
{
	wnd.clear(Color());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		return new StateDeath;
	return nullptr;
}

void StateDeath::onExit()
{
	Gui::gui.clear();
}

