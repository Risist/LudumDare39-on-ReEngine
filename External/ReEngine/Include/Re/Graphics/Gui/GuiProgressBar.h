#pragma once
#include <Re\Graphics\Gui\GuiButton.h>

namespace Gui
{
	class ProgressBar : public Base
	{
		virtual std::string getClassName() const override { return "ProgressBar"; }
	public:
		/// direction in which the bar wil aims
		enum Direction
		{
			left,
			right,
			up,
			down
		} direction;
		ProgressBar(const Vector2f& pos = Vector2f(), const Vector2f& halfWh = Vector2f(),
			State background = State(),
			State foreground = State(),
			float initialState = 1.f
		);
		ProgressBar(const string& path) { deserialise(path); }


		virtual void update(RenderTarget& wnd, RenderStates states) override;
		
		/// setters
		ProgressBar* setBackground(const State& s)
		{
			background = s;
			return this;
		}
		ProgressBar* setForeground(const State& s)
		{
			foreground = s;
			return this;
		}
		ProgressBar* setProgress(float32 s)
		{
			progress = clamp(s, 0.f, 1.f);
		}
		ProgressBar* setPos(const Vector2f& s)
		{
			pos = s;
			return this;
		}

		/// Color & texture of 
		State background; ///< back rectangle
		State foreground; ///< forward rectangle (showing progress)
		


		
		float32 getProgres() const { return progress; }

	private:
		/// actual progress of the bar. In range of[0,1] inclusive
		float progress;

	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};



}

