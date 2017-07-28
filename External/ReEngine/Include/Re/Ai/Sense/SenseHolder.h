#pragma once
#include <Re\Ai\Sense\SenseFilterBase.h>

namespace Sense
{
	class Holder
	{
	public:
		

		/// adds new filter to holder
		/// actors from this filter are added on next update;
		void addFilter(FilterBase* _new)
		{
			filters.push_back(unique_ptr<FilterBase>(_new) );
		}

		/// function which will be run on every actor within sense
		/// returns true if this query can be removed
		/// called once with nullptr as an argument at the begining of update
		typedef function<bool(Game::Actor*)> query_t;
		void addQuery(query_t _new)
		{
			queries.push_back(_new);
		}

		/// checks which actors are within sense and run rengistered queries
		void update();

		
	private:
		/// list of areas/ways to perceive other actors
		vector<unique_ptr<FilterBase>> filters;
		/// list of rengistered functions fun on every actor that is perceived by this sence
		vector<query_t> queries;
	};


}