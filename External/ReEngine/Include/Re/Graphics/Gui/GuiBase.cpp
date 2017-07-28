#include <Re\Graphics\Gui\GuiBase.h>

namespace Gui
{
	map<string, shared_ptr<Base> > *Base::loaded = nullptr;

	Base::Base(const sf::Vector2f& _pos) : pos(_pos) {}
	
	void Base::serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const
	{
		saver.save("posX", pos.x);
		saver.save("posY", pos.y);
		saver.save("hidden", hidden);
		saver.save("halfWhX", halfWh.x);
		saver.save("halfWhY", halfWh.y);

	}
	void Base::deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
	{
		pos.x = loader.load("posX", 0.f);
		pos.y = loader.load("posY", 0.f);
		halfWh.x = loader.load("halfWhX", 0.f);
		halfWh.y = loader.load("halfWhY", 0.f);

		setHidden( loader.load("hidden", false) );
	}


}