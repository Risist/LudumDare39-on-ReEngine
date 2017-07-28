#include <Re\Game\Actor\GameLayer.h>

namespace Game
{
	void Layer::onUpdate(sf::Time dt)
	{
		static list<Efect::Base*> toRemove;

		for (auto it = efects.begin(); it != efects.end(); )
			if ((*it)->readyToRemove && it->get()->onDeath(dt))
			{
				toRemove.push_back(it->release());
				efects.erase(it++);
			}
			else
				++it;

		for (auto &it : efects)
			if (it->activated)
				it->onUpdate(dt);

		for (auto it : toRemove)
		{
			delete it;
		}
		toRemove.clear();
	}
	Actor * Layer::addActor(Actor * _new)
	{
		assert(_new != nullptr);
		efects.push_back(unique_ptr<Base>(_new));
		_new->setActive(isActive());
		/// initialize
		_new->onInit();
		return _new;
	}
}