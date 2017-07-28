#pragma once
#include <Re\Ai\BehaviourTree\BtComposite.h>

namespace Bt
{

	class Selector : public Composite
	{
	public:
		State process() override;
	};

}