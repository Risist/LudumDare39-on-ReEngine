#include "StateCredits.h"
#include "StateMenu.h"


StateCredits::StateCredits()
{
}


void StateCredits::onStart()
{
	/// position of gui element
	Vector2D pos(550, 100);
	float offsetY = 60;

	Gui::gui.add(new Gui::Text("gui_text.txt"))->setPos(pos + Vector2D(-20, 0))
		->setSize(25)->setStr("  Ludum Dare 39 - Game"); pos.y += 100;
	Gui::gui.add(new Gui::Text("gui_text.txt"))->setPos(pos + Vector2D(-20, 0))
		->setSize(25)->setStr("  Credits"); pos.y += 100;


	Gui::gui.add(new Gui::Text("gui_text.txt"))->setPos(pos)
		->setSize(20)->setStr("Maciej  \"Risist\"  Dominiak"); pos.y += offsetY;

	Gui::gui.add(new Gui::Text("gui_text.txt"))->setPos(pos)
		->setSize(20)->setStr("--------------"); pos.y += offsetY;

	Gui::gui.add(new Gui::Text("gui_text.txt"))->setPos(pos)
		->setSize(20)->setStr("--------------"); pos.y += offsetY;

	auto back = Gui::gui.add(new Gui::NamedButton("gui_button.txt"))->setPos(pos)
		->setName("Back"); pos.y += offsetY;

	back->setEvent([]() { Game::stateManager.setState(new StateMenu); });
}

Game::State * StateCredits::onUpdate(sf::Time dt)
{
	wnd.clear(Color());
	return nullptr;
}

void StateCredits::onExit()
{
	Gui::gui.clear();
}

