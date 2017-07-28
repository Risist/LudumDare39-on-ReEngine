#pragma once
#include <Re\Graphics\Gui\GuiScrollBar.h>

namespace Gui
{

	class ColorBar : public Menu
	{
	public:
		ColorBar(const char* path);
		ColorBar(const Vector2f& halfWh = Vector2f(), float32 buttonSize = 10.f, float32 barOffset = 10.f);

		virtual void update(RenderTarget& wnd, RenderStates states) override;

		/// setters
		ColorBar* setColor(const sf::Color& cl);
		ColorBar* setPos(const sf::Vector2f& s)
		{
			pos = s;
			return this;
		}
		ColorBar* setColorBar(const Color& newColor);
		ColorBar* setColorButton(const Color& clOn, const Color& clOut, const Color& clPress);
		ColorBar* setBaseColor(Color cl)
		{
			barBaseColor = cl;
			return this;
		}
		ColorBar* setEvent(function<void(Color)> ev)
		{
			eventUpdate = ev;
			return this;
		}


		sf::Color getColor() const;
		

		shared_ptr<ScrollBar> _barRed;
		shared_ptr<ScrollBar> _barGreen;
		shared_ptr<ScrollBar> _barBlue;
		shared_ptr<ScrollBar> _barAlpha;
	
		Color barBaseColor;
		function<void(Color cl)> eventUpdate;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


}
