#include <Re\Graphics\Gui\GuiScrollBar.h>
#include <Re\Graphics\ResourceManager.h>

extern RenderWindow wnd;

namespace Gui
{
	ScrollBar::ScrollBar(sf::Vector2f & position, sf::Vector2f & halfWh, float32 scrollLenght,
		State stateBackground,
		State stateScrollOn, State stateScrollPressed, State stateScrollOut )
		:Menu(position), bBackground(new Button(stateBackground, Vector2f(), halfWh)),
		bScroll(new Button(Vector2f(), Vector2f(scrollLenght, halfWh.y) ,[](){}, stateScrollOn, stateScrollPressed, stateScrollOut))
	{
		add(bBackground,false);
		add(bScroll, false);
	}
	ScrollBar::ScrollBar(
		State stateBackground,
		State stateScroll,
		sf::Vector2f & position, sf::Vector2f & halfWh, float32 scrollLenght)
		:Menu(position), bBackground(new Button(stateBackground, Vector2f(), halfWh)),
		bScroll(new Button(Vector2f(), Vector2f(scrollLenght, halfWh.y), [&]() {scrollPressed = true; },
			stateScroll, stateScroll, stateScroll))
	{
		add(bBackground, false);
		add(bScroll, false);
	}


	void ScrollBar::update(sf::RenderTarget & target, sf::RenderStates states)
	{
		if (needToBeUpdated)
		{
			eventUpdateProgress(progress);
			needToBeUpdated = false;
		}

		if (direction == Direction::left)
		{
			bScroll->pos.x = -bBackground->halfWh.x + bScroll->halfWh.x
				+ (bBackground->halfWh.x - bScroll->halfWh.x)* 2.f * progress;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
				scrollPressed = false;
			Menu::update(target, states);
			if (scrollPressed)
			{
				eventUpdateProgress(progress);
				Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(wnd);
				float32 minimalPosition = getPosActual().x - bBackground->halfWh.x;

				progress = (mousePosition.x - minimalPosition) / (2 * bBackground->halfWh.x);
				progress = clamp(progress, 0.f, 1.f);
			}
		}
		else if (direction == Direction::up)
		{
			bScroll->pos.y = -bBackground->halfWh.y + bScroll->halfWh.y
				+ (bBackground->halfWh.y - bScroll->halfWh.y)* 2.f * progress;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
				scrollPressed = false;
			Menu::update(target, states);
			if (scrollPressed)
			{
				eventUpdateProgress(progress);
				Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(wnd);
				float32 minimalPosition = getPosActual().y - bBackground->halfWh.y;

				progress = (mousePosition.y - minimalPosition) / (2 * bBackground->halfWh.y);
				progress = clamp(progress, 0.f, 1.f);
			}
		}
		else
		{
			cerr << "wrong direction of scrollbar: " << direction << "\n";
		}
	}
	void ScrollBar::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{

	}
	void ScrollBar::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		string dir = loader.load<string>("direction", "left");
		if (dir == "left" || dir == "right")
			direction = Direction::left;
		else if (dir == "up" || dir == "down")
			direction = Direction::up;
		else
			cerr << "wrong direction of ScrollBar: \"" << dir <<"\"\n";
		Base::deserialiseF(file, loader);
		
		progress = loader.load("progress", 1.f);
		State stateBack;
		stateBack.cl = Color(
			loader.load("backClR", 255u),
			loader.load("backClG", 255u),
			loader.load("backClB", 255u),
			loader.load("backClA", 255u)
		);
		int ts = loader.load("backTs", (size_t)-1);
		if (ts != -1) stateBack.ts = tsInst[ts];


		///On
		State stateOn;
		stateOn.cl = Color(
			loader.load("onClR", 255u),
			loader.load("onClG", 255u),
			loader.load("onClB", 255u),
			loader.load("onClA", 255u)
		);
		ts = loader.load("onTs", (size_t)-1);
		if (ts != -1) stateOn.ts = tsInst[ts];


		///Out
		State stateOut;
		stateOut.cl = Color(
			loader.load("outClR", 255u),
			loader.load("outClG", 255u),
			loader.load("outClB", 255u),
			loader.load("outClA", 255u)
		);
		ts = loader.load("outTs", (size_t)-1);
		if (ts != -1) stateOut.ts = tsInst[ts];

		///On
		State statePress;
		statePress.cl = Color(
			loader.load("pressClR", 255u),
			loader.load("pressClG", 255u),
			loader.load("pressClB", 255u),
			loader.load("pressClA", 255u)
		);
		ts = loader.load("pressTs", (size_t)-1);
		if (ts != -1) statePress.ts = tsInst[ts];

		
		//create(direction, halfWh, loader.load("scrollLenght", 10.f), stateBack, stateOn, stateOut, statePress);
		set(halfWh, loader.load("scrollLenght", 10.f));
		bBackground->stateMouseOn = bBackground->stateMouseOut = bBackground->statePressed = stateBack;
		bScroll->stateMouseOn = stateOn;
		bScroll->stateMouseOut = stateOut;
		bScroll->statePressed = statePress;
	}
}