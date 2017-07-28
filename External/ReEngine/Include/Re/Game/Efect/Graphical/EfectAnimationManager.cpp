#include <Re\Game\Efect\Graphical\EfectAnimationManager.h>

namespace Efect
{

	void AnimationManager::onUpdate(sf::Time dt)
	{
		//controllers[0].onUpdateModel();
		//for (auto& it : controllers)
		//	it.onUpdateModel();

		auto itScale = controllersScale.begin();
		for (auto it = controllers.begin(); it < controllers.end(); )
		{
			//if (*itScale)
				(*it)->onUpdateModel(*itScale);
			++it;
			++itScale;
		}
	}

	AnimationManager * AnimationManager::activateOneAnimation(size_t id, Graphics::Step_t scale)
	{
		for (auto& it : controllersScale)
			it = 0.f;
		scaleSum = controllersScale[id] = scale;
		return this;
	}

}