#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Ai\Sense\sense.h>

namespace Efect
{
	/// lookups through the phisycal world for objects that fits to sensing model of agent
	/// Then other components can use stored actors to reason on them
	class Sensor : public Base
	{
	public:
		Sensor(sf::Time refreshRate = sf::seconds(0));

		/// initialisation functions

		Sensor* addQuery(Sense::Holder::query_t query)
		{
			holder.addQuery(query);
			return this;
		}
		Sensor* addFilter(Sense::FilterBase* filter)
		{
			filter->owner = getOwner();
			holder.addFilter(filter);
			return this;
		}

		/// utility functions

		void onUpdate(sf::Time dt) override;

		sf::Time refreshCd;
	private:
		Clock refreshClock;
		Sense::Holder holder;
	};
}