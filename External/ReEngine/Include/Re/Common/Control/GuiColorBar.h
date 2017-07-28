#pragma once
#include <Re\Graphics\Gui\GuiSetBar.h>

namespace Gui
{

	class ColorBar : public Menu
	{
	public:

		virtual void update(RenderTarget& wnd, RenderStates states) override;

		sf::Color getColor() const;
		void setColor(const sf::Color& cl);


		shared_ptr<SetBar> _barRed;
		shared_ptr<SetBar> _barGreen;
		shared_ptr<SetBar> _barBlue;
		shared_ptr<SetBar> _barAlpha;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


}
