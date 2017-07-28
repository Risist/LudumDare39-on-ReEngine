#pragma once
#include <Re\Common\utility.h>
//#include <Re\Game\GameActor.h>
namespace Game { class Actor; }

namespace Sense
{
	class Holder;


	/// base class for sensory filtering
	class FilterBase
	{
	public:
		typedef function<bool(Game::Actor*)> filtering_t;
		FilterBase(filtering_t _addictionalFiltering = [](Game::Actor*) {return true; })
			: addictionalFiltering(_addictionalFiltering)
		{

		}

		/// returns whether or not given actor is in sensory field 
		virtual bool filter(Game::Actor*) = 0;

		/// beside (mostly) geometrical filtering sometimes you can face need 
		// of filtering among more game specific data - there is place to do so
		filtering_t addictionalFiltering;

		/// owner of this filter -> setted up by owning efect
		/// use it post initialization
		Game::Actor* owner;
	private:

		/// Efect::Sensor sould use both functor and virtual versions
		bool __filter(Game::Actor* actor)
		{
			return addictionalFiltering(actor) && filter(actor);
		}

		friend Holder;
	};

}