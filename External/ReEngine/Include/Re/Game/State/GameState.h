#pragma once
#include <Re\Common\utility.h>

namespace Game
{
	class State
	{
	public:
		/// constructor; initialize there heavy resources
		State();
		virtual ~State(){};

		/// called when the state is choosen to be actual
		virtual void onStart();
		/// called when another state is choosen to be actual
		virtual void onExit();

		// return: if returns nullptr does nothing
		//			otherwise changes active state to returned value
		//			and calls onExit function
		virtual State* onUpdate( sf::Time dt = sf::seconds(1) ) = 0;


	};

}

