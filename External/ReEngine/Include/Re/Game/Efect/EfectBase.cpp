#include <Re\Game\Efect\EfectBase.h>
namespace Efect
{
	Base::Base()
		: owner(nullptr),
		activated(true),
		readyToRemove(false)
	{
	}
}