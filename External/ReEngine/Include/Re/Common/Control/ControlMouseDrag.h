#pragma once
#include <Re\Common\Settings.h>

namespace Control
{
	/// class which measures mouse movement
	/// and locks mouse on the window
	class MouseDrag
	{
	public:
		MouseDrag();


		/// count new offset
		/// designed to be called every frame
		Vector2f measure();
		/// locks mouse on window
		/// should be called every frame to work
		/// @offset tells how big is area in which mouse is "transported" to other side
		void loopMouse(Vector2f offset);


		/// saved last pos of mouse
		Vector2f lockedPoint;

	private:
		bool locked;
	};
}