#include <Re\ReEngine.h>
#include "StateGame.h"
#include "StateMenu.h"

//#define TEST_FPS

void init()
{
	srand((unsigned int)time(nullptr));
	wnd.create(VideoMode(1100, 750), "LudumDare 39 Game");
	//wnd.setVerticalSyncEnabled(true);
	wnd.setFramerateLimit(30);

	cam.create(Vector2D(wnd.getSize().x, wnd.getSize().y));
	cam.setDarkness(1.f);
	cam.setBackgroundColor(Color(200u, 200u, 200u));

	res.deserialise("Resources.txt");


	//Game::stateManager.setState( new StateGame() );
	Game::stateManager.setState(new StateMenu);

}


void update()
{
	static Clock clock, performanceClock;
	performanceClock.restart();
	Game::stateManager.onUpdate(clock.getElapsedTime());

#ifdef TEST_FPS
	sf::Text txt;
	{
		static int32 average = performanceClock.getElapsedTime().asMilliseconds();
		average = (average * 7 + performanceClock.getElapsedTime().asMilliseconds()) *0.125;

		txt.setPosition(0, 0);
		txt.setFont(res.fonts[1]);
		txt.setCharacterSize(35);
		txt.setFillColor(Color::White);
		txt.setStyle(sf::Text::Bold);
		std::stringstream ss;
		ss << "ms: " << average;
		txt.setString(ss.str());
	}
	wnd.draw(txt);
#endif
	clock.restart();
	
	Gui::gui.update(wnd, RenderStates::Default);
}
void out()
{

}


int main()
{
	init();

	while (wnd.isOpen())
	{
		actionMap.clearEvents();
		Event ev;
		while (wnd.pollEvent(ev))
		{
			if (ev.type == Event::Closed
				|| (ev.type == Event::KeyPressed && ev.key.code == sf::Keyboard::Escape))
				wnd.close();
			actionMap.pushEvent(ev);
		}
		update();

		wnd.display();
	}
	out();
}