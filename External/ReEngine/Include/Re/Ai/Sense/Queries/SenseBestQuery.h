#pragma once
#include <Re\Ai\Sense\SenseHolder.h>

namespace Sense
{
	class BestQuery
	{
	public:
		typedef function<float32(Game::Actor*)> evaluate_t;
		typedef function<bool(Game::Actor*)> result_t;
		BestQuery(evaluate_t evaluate, result_t result);

		bool operator() (Game::Actor* actor);

		evaluate_t evaluate;
		result_t result;
		
	private:
		float32 bestEvaluation;
		Game::Actor* bestActor;
	};
}