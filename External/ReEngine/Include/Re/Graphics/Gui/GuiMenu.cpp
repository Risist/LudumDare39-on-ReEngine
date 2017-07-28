#include <Re\Graphics\Gui\Gui.h>
#include <Re\Graphics\Gui\GuiSpecial.h>

namespace Gui
{
	Menu::Menu(const sf::Vector2f& pos, const initializer_list<shared_ptr<Base>>& initial)
		: Base(pos)
	{
		create(initial);
	}


	void Menu::create(const initializer_list<shared_ptr<Base>>& toAdd)
	{
		for (auto it : toAdd)
			add( it );
	}

	void Menu::update(RenderTarget& wnd, RenderStates states)
	{
		for each(auto it in el)
			if (it && it->isHidden() == false) // update an element if is not hidden
			{
				it->updatePosActual(getPosActual());
				it->update(wnd, states);
			}
	}
	void Menu::updateHidden(bool s)
	{
		for each(auto it in el)
			it->updateHidden(s);
	}

	void Menu::add(shared_ptr<Base> s, bool hidden )
	{
		el.push_back(s);
		s->setHidden(hidden);
	}
	void Menu::clear()
	{
		el.clear();
	}


	shared_ptr<Base> Menu::createElement(const string& className)
	{
#define CASE_DEF(Class) if( className == #Class ) return make_shared<Class>();
		
		CASE_DEF(Menu)
		else CASE_DEF(Button)
		else CASE_DEF(Text)
		else CASE_DEF(CheckBox)
		else CASE_DEF(ProgressBar)
		else CASE_DEF(ScrollBar)
		else CASE_DEF(SetBar)
		else CASE_DEF(ColorBar)
		else CASE_DEF(Inspector)
		else CASE_DEF(NamedButton)

		/// UNDEFINED class type
		cerr << "Error: You are trying to create " << className << " gui element which does not exist\n";
		return shared_ptr<Base>();
#undef CASE_DEF
	}
	shared_ptr<Base> Menu::desetializeInclude(Res::DataScriptLoader & loader)
	{
		string path = loader.loadRaw("path", "wrong_path");
		if (path == "wrong_path")
			cerr << "At menu deserialize include path is not set\n";
		ifstream file(path);
		if (file)
		{
			Res::DataScriptLoader _loader;
			_loader.nextLine(file);
			string type = _loader.load<string>("type", "UNDEFINED");
			auto sh = createElement(type);
			if (sh)
			{
				sh->deserialise(file, _loader);
				return sh;
			}
		}
		else
			cerr << "failed to open the file to load: \"" << path << "\"";

		return shared_ptr<Base>();
	}
	void Menu::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Base::serialiseF(file, saver);
		
		auto it = el.begin();
		{
			saver.save("type", (*it)->getClassName() );
			(*it)->serialise(file, saver);
		}
		DATA_SCRIPT_MULTILINE_SAVE(file, saver, it != el.end());
	}
	void Menu::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);
		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string type = loader.load<string>("type", "UNDEFINED");

			shared_ptr<Base> sh;

			/// include the element from other file
			if (type == "Include")
			{
				sh = desetializeInclude(loader);
				if (sh)
				{
					Vector2D pos(loader.load("posX", 0.f), loader.load("posY", 0.f));
					bool hidden = loader.load("hidden", false);
					sh->setPos(pos + sh->pos);
					sh->setHidden(hidden);
				}
			}
			else {
				sh = createElement(type);
				if (sh) sh->deserialise(file,loader);
			}

			if (sh) /// load from file all propertites of newly created element
			{
				add(sh, (*sh).isHidden());
				if (loaded)
				{
					/// give an ability to set up events after loading from file
					/// loaded map must be assigned
					string name = loader.load<string>("name", "___TRASH");
					if (name != "___TRASH")
					{
						(*loaded)[name] = sh;
					}
				}
			}

			///
		}
	}

}/// namespace