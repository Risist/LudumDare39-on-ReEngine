#include <Re\Graphics\Gui\GuiSetBar.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	SetBar::SetBar()
		: bBackground( new Button() ),
		bPlus(new Button()),
		bMinus(new Button()),
		tText(new Text()),
		minimalValue( -std::numeric_limits<float32>::max()),
		maximalValue(std::numeric_limits<float32>::max())
	{
		add(bBackground);
		add(bPlus);
		add(bMinus);
		add(tText);

		bPlus->eventOnPress = [&]() { 
				if (timerPress.isReadyRestart() == false) return; 
				progress += increaseValue(); eventUpdateProgress(progress); 
		};
		bMinus->eventOnPress = [&]() { 
			if (timerPress.isReadyRestart() == false) return;
			progress -= increaseValue(); eventUpdateProgress(progress); 
		};
		bBackground->eventOnPress = [&]() { 
			if (timerPress.isReadyRestart() == false) return;
			progress = initialValue; eventUpdateProgress(progress); 
		};
	}

	SetBar::SetBar(const char * path)
		:bBackground(new Button()),
		bPlus(new Button()),
		bMinus(new Button()),
		tText(new Text()),
		minimalValue(-std::numeric_limits<float32>::max()),
		maximalValue(std::numeric_limits<float32>::max())
	{
		add(bBackground);
		add(bPlus);
		add(bMinus);
		add(tText);

		bPlus->eventOnPress = [&]() {
			if (timerPress.isReadyRestart() == false) return; 
			progress = clamp(progress + increaseValue(), minimalValue, maximalValue);
			eventUpdateProgress(progress);
		};
		bMinus->eventOnPress = [&]() {
			if (timerPress.isReadyRestart() == false) return; 
			progress = clamp(progress - increaseValue(), minimalValue, maximalValue);
			eventUpdateProgress(progress);
		};
		bBackground->eventOnPress = [&]() {
			if (timerPress.isReadyRestart() == false) return;
			progress = clamp(initialValue, minimalValue, maximalValue);
			eventUpdateProgress(progress);
		};

		deserialise(path);
	}

	void SetBar::update(RenderTarget & wnd, RenderStates states)
	{
		progress = clamp(progress, minimalValue, maximalValue);

		if (needToBeUpdated)
		{
			eventUpdateProgress(progress);
			needToBeUpdated = false;
		}

		if (addictionalPressPlus() && timerPress.isReadyRestart())
		{
			progress = clamp(progress + increaseValue(), minimalValue, maximalValue);
			eventUpdateProgress(progress);
		}
		else if (addictionalPressMinus() && timerPress.isReadyRestart())
		{
			progress = clamp(progress - increaseValue(), minimalValue, maximalValue);
			eventUpdateProgress(progress);
		}

		(*tText).clear() << name << progress;
		Menu::update(wnd,states);
	}

	void SetBar::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}

	void SetBar::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);

		float32 buttonSize = loader.load("buttonSize", 10.f );
		name = loader.loadRaw("barName", "");

		bBackground->halfWh = halfWh - sf::Vector2f(buttonSize*2,0);
		bPlus->halfWh = Vector2f(buttonSize, halfWh.y);
		bMinus->halfWh = Vector2f(buttonSize, halfWh.y);
		bPlus->pos.x = +halfWh.x - buttonSize;
		bMinus->pos.x = -halfWh.x + buttonSize;

		initialValue = progress = loader.load("progress", 0.f);
		increaseValue = loader.load("increase", 1.f);

		tText->txt.setFillColor(
			Color(
				loader.load("textClR", 255),
				loader.load("textClG", 255),
				loader.load("textClB", 255),
				loader.load("textClA", 255)
				)
		);
		tText->txt.setCharacterSize(loader.load("txtSize", 25u ));

		timerPress.cd = sf::seconds(loader.load("timerCd", 0.f));
		minimalValue = loader.load("minimalProgress", -std::numeric_limits<float32>::max());
		maximalValue = loader.load("maximalProgress", std::numeric_limits<float32>::max());

#define loadState(stateName1, stateName2, stateCode)		{							\
		int ts = loader.load(stateCode + "Ts", (size_t)-1);								\
		if (ts != -1) stateName2 .ts = stateName1 .ts = tsInst[ts];					\
		stateName1.cl.r = stateName2.cl.r = loader.load(stateCode + "ClR", 255);		\
		stateName1.cl.g = stateName2.cl.g = loader.load(stateCode + "ClG", 255);		\
		stateName1.cl.b = stateName2.cl.b = loader.load(stateCode + "ClB", 255);		\
		stateName1.cl.a = stateName2.cl.a = loader.load( stateCode + "ClA", 255); }

#define loadStateAll(stateName, stateCode)										\
		{																		\
			int ts = loader.load(stateCode + "Ts", (size_t)-1);					\
			if (ts != -1) 														\
			{																	\
				stateName->stateMouseOn.ts =									\
				stateName->stateMouseOut.ts =									\
				stateName->statePressed.ts = tsInst[ts];						\
			}																	\
			stateName->stateMouseOn.cl.r =										\
			stateName->stateMouseOut.cl.r =										\
			stateName->statePressed.cl.r = loader.load(stateCode + "ClR", 255);	\
			stateName->stateMouseOn.cl.g =										\
			stateName->stateMouseOut.cl.g =										\
			stateName->statePressed.cl.g = loader.load(stateCode + "ClG", 255);	\
			stateName->stateMouseOn.cl.b =										\
			stateName->stateMouseOut.cl.b =										\
			stateName->statePressed.cl.b = loader.load(stateCode + "ClB", 255);	\
			stateName->stateMouseOn.cl.a =										\
			stateName->stateMouseOut.cl.a =										\
			stateName->statePressed.cl.a = loader.load(stateCode + "ClA", 255);	\
		}																		\

		loadState(bPlus->stateMouseOn, bMinus->stateMouseOn, string("on"));
		loadState(bPlus->stateMouseOut, bMinus->stateMouseOut, string("out"));
		loadState(bPlus->statePressed, bMinus->statePressed, string("press"));

		loadStateAll(bBackground, string("back"));

#undef loadState
#undef loadStateAll

	}

}