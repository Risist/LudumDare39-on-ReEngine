#pragma once
#include <Re\Graphics\Gui\GuiBase.h>


namespace Gui
{
	/// Gui class used to connect and treat many gui elements as one
	class Menu : public Base
	{
		virtual std::string getClassName() const override { return "Menu"; }
	public:
		Menu(const Vector2f& pos = Vector2f(), const initializer_list<shared_ptr<Base>>& initial = {});


		Menu* setPos(const Vector2f& s)
		{
			pos = s;
			return this;
		}

		/// add many gui elements at once
		void create(const initializer_list<shared_ptr<Base>>& toAdd );

		void update(RenderTarget& wnd, RenderStates states) override;
		void updateHidden(bool s) override;

		template<class T>
		T* add(T* s, bool hidden = false)
		{
			add(shared_ptr<Base>(s), hidden);
			return s;
		}
		void add(shared_ptr<Base> s, bool hidden = false);
		
		shared_ptr<Base> operator[](size_t id)
		{
			return el[id];
		}

		/// remove all menu elements
		void clear();
		/// how many gui elements are contained?
		size_t getSize() { return el.size(); }

	protected:
		/// vector of contained elements
		vector<shared_ptr<Base>> el;


	protected:
		/// creates a new Gui element
		/// returns shared ptr with nullptr if className type does not exist
		shared_ptr<Base> createElement(const string& className);

		/// Graphical propertites saved in files 
		shared_ptr<Base> desetializeInclude(Res::DataScriptLoader& loader);
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}