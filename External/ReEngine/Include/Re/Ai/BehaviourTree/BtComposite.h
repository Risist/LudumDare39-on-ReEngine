#pragma once
#include <Re\Ai\BehaviourTree\BtBase.h>

namespace Bt
{
	/// class which adds common features of all composite elements
	class Composite : public Base
	{
	public:
		Composite() {};
		
		void onEnter() override
		{
			actualProceedElement = elements.begin();
			(*actualProceedElement)->onEnter();
		}
		void onExit() override
		{
			actualProceedElement = elements.begin();
			(*actualProceedElement)->onExit();
		}

		/// add a new element in cin/cout notation ( cmp->add(sh1)->add(sh2)->add(sh2) ect. )
		template<class T>
		Composite* add(T* newChild)
		{
			elements.push_back(make_unique<T>(newChild));
			return this;
		}

	protected:
		/// container for base elements
		vector<unique_ptr<Base>> elements;
		typedef vector<unique_ptr<Base>>::iterator IteratorElement;

		IteratorElement actualProceedElement;
	};


}