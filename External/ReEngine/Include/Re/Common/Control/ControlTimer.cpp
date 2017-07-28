#include <Re\Common\Control\ControlTimer.h>

namespace Control
{



	void Timer::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("cd", cd.asSeconds());
	}

	void Timer::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		cd = sf::seconds(loader.load("cd", 0.f) );
	}

}