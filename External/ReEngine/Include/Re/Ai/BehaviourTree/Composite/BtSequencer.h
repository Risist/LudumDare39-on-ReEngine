#pragma once
#include <Re\Ai\BehaviourTree\BtComposite.h>

namespace Bt
{
	class Sequencer : public Composite
	{
	public:
		State process() override;
	};


}