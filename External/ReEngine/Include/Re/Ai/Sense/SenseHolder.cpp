#include <Re\Ai\Sense\SenseHolder.h>
#include <Re\Game\GameWorld.h>

namespace Sense
{
	void Holder::update()
	{
		auto &actorList = Game::world.getActorList();

		for (auto queryIt = queries.begin(); queryIt != queries.end();)
			if ((*queryIt)(nullptr))
				queries.erase(queryIt++);
			else
				++queryIt;

		for (auto actorIt : actorList)
			for (auto filterIt = filters.begin(); filterIt != filters.end(); ++filterIt)
				if ( (*filterIt)->__filter(actorIt))
				{
					/// iterate through all queries
					for (auto queryIt = queries.begin(); queryIt != queries.end(); ++ queryIt)
						(*queryIt)(actorIt);

					/// the actor was proceed - move to next, do not check other actors
					break;
				}

	}
}