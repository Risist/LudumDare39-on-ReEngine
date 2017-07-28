#include <Re\Graphics\Gui\GuiText.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	Text::Text()
	{
		txt.setFont(res.fonts[1]);
	}
	Text::Text(const char * path)
	{
		deserialise(path);
	}

	void Text::update(RenderTarget & target, RenderStates states)
	{
		txt.setString(str);
		txt.setPosition(getPosActual());
		
		/// multiplaying in X axes by 0.25 seems to work
		/// Probably because of twice multiplaying by 0.5 ( from size and character size)
		/// Take care over that
		txt.setOrigin(static_cast<float>(str.size()* txt.getCharacterSize()) *0.25f,
			static_cast<float>(txt.getCharacterSize())*0.5f);

		target.draw(txt, states);
	}

	void Text::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}

	void Text::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file,loader);
		
		str = loader.loadRaw("str", "");

		Color cl;
		cl.r = loader.load("clR", 255);
		cl.g = loader.load("clG", 255);
		cl.b = loader.load("clB", 255);
		cl.a = loader.load("clA", 255);
		txt.setFillColor(cl);
		txt.setCharacterSize(loader.load("size", 25));


		txt.setFont(fontInst[loader.load("font", (ResId)1)]);
	}

}