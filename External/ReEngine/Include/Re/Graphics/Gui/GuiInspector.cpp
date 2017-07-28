#include <Re\Graphics\Gui\GuiInspector.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{



	Inspector::Inspector()
		:sScroll( new ScrollBar),
		bBackground( new Button)
	{
		add(bBackground);
		add(sScroll);
	}

	void Inspector::update(RenderTarget & target, RenderStates states)
	{
		///TODO Fix hiding Inspector elements

		//Menu::update(target, states);	
		for each(auto it in el)
			if (it && it->isHidden() == false) // update an element if is not hidden
			{
				if (it == bBackground || it == sScroll)
					it->updatePosActual(getPosActual());
				else
				{
					Vector2f pos = Vector2f(0, 2*sScroll->getProgres() *(fieldLenght - bBackground->halfWh.y));
					if (pos.y + it->pos.y + it->halfWh.y > halfWh.y ||
						pos.y + it->pos.y + it->halfWh.y < -halfWh.y)
						continue;
					it->updatePosActual(getPosActual() + pos);
				}
				it->update(target, states);
			}
	}

	void Inspector::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}

	void Inspector::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		bBackground->halfWh.x = loader.load("halfWhX", 0.f);
		bBackground->halfWh.y = loader.load("halfWhY", 0.f);
		
		fieldLenght = loader.load("fieldLenght", bBackground->halfWh.y);

		Color clBackground((sf::Uint8)loader.load("backClR", 255),
			(sf::Uint8)loader.load("backClG", 255),
			(sf::Uint8)loader.load("backClB", 255),
			(sf::Uint8)loader.load("backClA", 255)
		);
		bBackground->stateMouseOn.cl = clBackground;
		bBackground->stateMouseOut.cl = clBackground;
		bBackground->statePressed.cl = clBackground;

		int ts = loader.load("backTs", -1);
		if (ts != -1) bBackground->stateMouseOn.ts =
			bBackground->stateMouseOut.ts =
			bBackground->statePressed.ts = tsInst[ts];

		float32 scrollLenght = loader.load("scrollLenght", 10.f);
		float32 scrollWidth = loader.load("scrollWidth", 10.f);
		sScroll->setPos( Vector2f(bBackground->halfWh.x-scrollLenght,0));

		State stateBack;
		stateBack.cl = Color(
			(sf::Uint8)loader.load("backClR", 255u),
			(sf::Uint8)loader.load("backClG", 255u),
			(sf::Uint8)loader.load("backClB", 255u),
			(sf::Uint8)loader.load("backClA", 255u)
		);
		ts = loader.load("backTs", -1);
		if (ts != -1) stateBack.ts = tsInst[ts];

		/// backScroll
		State stateBackScroll;
		stateBackScroll.cl = Color(
			(sf::Uint8)loader.load("backScrollClR", 255u),
			(sf::Uint8)loader.load("backScrollClG", 255u),
			(sf::Uint8)loader.load("backScrollClB", 255u),
			(sf::Uint8)loader.load("backScrollClA", 255u)
		);
		ts = loader.load("backScrollTs", -1);
		if (ts != -1) stateBackScroll.ts = tsInst[ts];

		///On
		State stateOn;
		stateOn.cl = Color(
			(sf::Uint8)loader.load("onClR", 255u),
			(sf::Uint8)loader.load("onClG", 255u),
			(sf::Uint8)loader.load("onClB", 255u),
			(sf::Uint8)loader.load("onClA", 255u)
		);
		ts = loader.load("onTs", -1);
		if (ts != -1) stateOn.ts = tsInst[ts];


		///Out
		State stateOut;
		stateOut.cl = Color(
			(sf::Uint8)loader.load("outClR", 255u),
			(sf::Uint8)loader.load("outClG", 255u),
			(sf::Uint8)loader.load("outClB", 255u),
			(sf::Uint8)loader.load("outClA", 255u)
		);
		ts = loader.load("outTs", -1);
		if (ts != -1) stateOut.ts = tsInst[ts];

		///On
		State statePress;
		statePress.cl = Color(
			(sf::Uint8)loader.load("pressClR", 255u),
			(sf::Uint8)loader.load("pressClG", 255u),
			(sf::Uint8)loader.load("pressClB", 255u),
			(sf::Uint8)loader.load("pressClA", 255u)
		);
		ts = loader.load("pressTs", -1);
		if (ts != -1) statePress.ts = tsInst[ts];
		
		//sScroll->create(ScrollBar::up, Vector2f(scrollWidth, bBackground->halfWh.y),
		//	scrollLenght,
		//	stateBackScroll, stateOn, stateOut, statePress);
		sScroll->set(Vector2f(scrollWidth, bBackground->halfWh.y), scrollLenght)
			->setDirection(ScrollBar::up);

		sScroll->bBackground->stateMouseOn = sScroll->bBackground->stateMouseOut = sScroll->bBackground->statePressed = stateBack;
		sScroll->bScroll->stateMouseOn = stateOn;
		sScroll->bScroll->stateMouseOut = stateOut;
		sScroll->bScroll->statePressed = statePress;

		Menu::deserialiseF(file, loader);
	}

}