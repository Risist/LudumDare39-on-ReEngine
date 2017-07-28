#pragma once
#include <vector>
#include <initializer_list>

using namespace std;

/*
class which supports choosing randomly from many possiblites wih non-equal probablity

usage: 
fill chances vector with chances of each possiblity and remember ids of them

then use randId function to rand new id

warring: before usage there is need to write somewhere : srand(time(nullptr));
*/
class RandomChance
{
public:
	RandomChance();
	RandomChance( const initializer_list<float>& chances);

	void set(const initializer_list<float>& list);
	size_t randId() const;

	vector<float> chances;
};

