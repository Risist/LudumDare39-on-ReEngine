#include <Re\Common\RandomChance.h>
#include <Re\Common\Math\Math.h>


RandomChance::RandomChance()
{
}

RandomChance::RandomChance(const initializer_list<float>& _chances)
	: chances(_chances)
{
}

void RandomChance::set(const initializer_list<float>& list)
{
	chances.resize(list.size());
	int i = 0;
	for (auto &it: list)
	{
		chances[i] = it;
		++i;
	}
}

size_t RandomChance::randId() const
{
	// sum up all chances;
	float sum = 0;
	for (float chanceIt : chances)
		sum += chanceIt;

	// rand noumber in proper range
	float randedNoumber = randRange(0, sum);

	// find id of interval randedNoumber fits in
	float lastNoumber = 0;
	for (size_t i = 0; i < chances.size(); ++i)
		if( randedNoumber > lastNoumber && randedNoumber < lastNoumber + chances[i])
		{
			return i;
		}
		else
		{
			randedNoumber += chances[i];
		}

	// something goes wrong
	// there is no noumber that fits in
	assert(false);
	return -1;
}
