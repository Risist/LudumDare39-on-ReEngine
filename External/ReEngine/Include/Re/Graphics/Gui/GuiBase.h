#pragma once

#include <Re\Common\utility.h>

namespace Gui
{
	/// Base gui fragment class
	/// Prepared for serialisation/deserialisation or manual setting
	class Base : public Res::ISerialisable
	{
	public:
		/// to give yourself a chance to assign events within gui elements
		/// set up the loaded map to your container
		/// and set in file name you will use as the key
		/// eg. <name =wtf?> warring: "___THRASH" name is reserved
		static map<string, shared_ptr<Base> >*loaded;
	public:
		Base(const Vector2f& pos = Vector2f());
		virtual ~Base() {}

		// display and update gui element
		virtual void update(RenderTarget& wnd, RenderStates states) = 0;
		
		/// needed to file saving
		virtual std::string getClassName() const { return "UNDEFINED"; }

		// set pos relative to pos of element connected to
		void updatePosActual(const Vector2f pos = Vector2f())
		{
			posActual = Base::pos + pos;
		}
		const Vector2f& getPosActual() const
		{
			return posActual;
		}

		Base* setPos(const sf::Vector2f& _new)
		{
			pos = _new;
			return this;
		}		
		Base* setHidden(bool s)
		{
			hidden = s;
			updateHidden(s);
			return this;
		}
		bool isHidden() const
		{
			return hidden;
		}

		/// which area the object holds
		Vector2f halfWh;
		/// offset of pos relative to parent transform
		Vector2f pos;

	protected:
		/// catch event of changing visibility of gui object
		virtual void updateHidden(bool s) {}
		/// hidden gui object is not updated nor drawn onto the screan
		bool hidden;

		// actual pos of gui element
		Vector2f posActual;
		
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	
	
		friend class Menu;
	};
}