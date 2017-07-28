#include <Re\Game\Efect\Sensor\EfectSensor.h>


namespace Efect
{
	Sensor::Sensor(sf::Time refreshRate)
		: refreshCd(refreshRate)
	{
	}
	void Sensor::onUpdate(sf::Time dt)
	{
		if (refreshClock.getElapsedTime() > refreshCd)
		{
			holder.update();
			refreshClock.restart();
		}
	}
}