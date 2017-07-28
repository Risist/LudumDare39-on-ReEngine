#include <Re\Ai\Sense\Queries\SenseBestQuery.h>

namespace Sense
{

	BestQuery::BestQuery(evaluate_t _evaluate, result_t _result)
		:evaluate(_evaluate), result(_result)
	{
	}

	bool BestQuery::operator()(Game::Actor * actor)
	{
		if (actor)
		{
			float32 evaluation = evaluate(actor);
			if (evaluation > bestEvaluation)
			{
				bestEvaluation = evaluation;
				bestActor = actor;
			}
		}
		else
		{
			bestEvaluation = -99999999999999;
			bestActor = nullptr;
		}
		return result(bestActor);
	}

}