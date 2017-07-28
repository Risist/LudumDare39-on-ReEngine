#pragma once

#include <Re\Graphics\Gui\GuiBase.h>

namespace Gui
{
	class Text : public Base
	{
		virtual std::string getClassName() const override { return "Text"; }
	public:
		Text();
		Text(const char* path);

		virtual void update(RenderTarget& target, RenderStates states) override;

		///setters
		template<class T>
		Text* setStr(T s)
		{
			(*this) << s;
			return this;
		}
		Text* setPos(const Vector2f& pos)
		{
			Base::setPos(pos);
			return this;
		}
		Text* setColor(Color color)
		{
			txt.setFillColor(color);
			return this;
		}
		Text* setSize(unsigned int s)
		{
			txt.setCharacterSize(s);
			return this;
		}
		Text* setOutlineColor(Color color)
		{
			txt.setOutlineColor(color);
			return this;
		}
		Text* setOutlineThickness(float s)
		{
			txt.setOutlineThickness(s);
			return this;
		}
		Text* setStyle(sf::Uint32 style)
		{
			txt.setStyle(style);
			return this;
		}



		/// stream
		template<typename T>
		Text& operator<<(T s)
		{
			std::ostringstream stream;
			stream << s;
			str += stream.str();

			return *this;
		}
		Text& operator<<(const std::string& s)
		{
			str += s;
			return *this;
		}
		Text& operator<<(const char* s)
		{
			str += s;
			return *this;
		}


		Text& clear()
		{
			str = "";
			return *this;
		}

		// graphical representation of text
		sf::Text txt;
		// what is to write
		string str;

	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}