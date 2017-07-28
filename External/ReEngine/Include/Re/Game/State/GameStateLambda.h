#pragma once
#include <Re\Game\State\GameState.h>
#include <functional>

namespace Game
{
	/*
	State wrapper to allow faster prototyping - you can define state in place
	And move to another file when you will really need that (or things placed here will become larger)
	*/
	class StateLambda : public State
	{
	public:
		StateLambda( 
			function<void()> __onStart = defaultOnStart,
			function<State*(sf::Time dt)> __onUpdate = defaultOnUpdate,
			function<void()> __onExit = defaultOnExit
			):
			_onStart(__onStart),
			_onExit(__onExit),
			_onUpdate(__onUpdate)
		{

		}

		/// overrides
		virtual void onStart() override;
		virtual void onExit() override;
		virtual State* onUpdate(sf::Time dt) override;

		/// defaults 
		static void defaultOnStart();
		static void defaultOnExit();
		static State* defaultOnUpdate(sf::Time dt);

	private:
		function<void()> _onStart;
		function<void()> _onExit;
		function<State*(sf::Time dt)> _onUpdate;
	};
}