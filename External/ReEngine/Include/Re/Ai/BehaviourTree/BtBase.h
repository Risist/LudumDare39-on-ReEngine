#pragma once
/// uncomment when implementing script saving nodes data 
//#include <Re\Common\Scripts\ResScripts.h>
#include <Re\Common\Settings.h>

/// behaviour trees
namespace Bt
{
	/// Base class for all behaviour tree elements
	class Base
	{
	public:
		/// enum to hold result of BT element
		enum class State : uint8	
		{
			succed		= 0,
			failiture	= 1,
			running		= 2,
		};

		virtual State process() =0;
		/// called when Node will be choosen for processing
		virtual void onEnter()	=0;
		/// called when Node will return something other than running
		virtual void onExit()	=0;
	};

}