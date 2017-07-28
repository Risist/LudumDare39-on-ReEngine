#pragma once
#include <Re\Ai\BehaviourTree\BtBase.h>

namespace Bt
{
	class Decorator : public Base
	{
	public:
		Decorator(Base* _child)
			: child(_child)
		{
		}
		
		void onEnter() override
		{
			child->onEnter();
		}
		void onExit() override
		{
			child->onExit();
		}



	//protected:
		unique_ptr<Base> child;
	};

}