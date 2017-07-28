#pragma once
#include <Re\Graphics\Gui\GuiMenu.h>
#include <Re\Graphics\Gui\GuiScrollBar.h>
#include <Re\Graphics\Gui\GuiButton.h>

namespace Gui
{
	/// class for editor, can contain many setbars or similar
	/// has a scrollbar, with which you can slide over parametrs that are not visible 
	class Inspector : public Menu
	{
	public:
		Inspector();

		virtual void update(RenderTarget& target, RenderStates states) override;


		shared_ptr<ScrollBar> sScroll;
		shared_ptr<Button> bBackground;

		float32 fieldLenght;

	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}
