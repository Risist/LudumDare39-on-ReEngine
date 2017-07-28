#pragma once
#include <Re\Common\Scripts\ResScripts.h>
#include <Re\Common\Settings.h>


namespace Control
{
	/// simple timer class
	class Timer : public Res::ISerialisable
	{
	public:
		Timer(sf::Time _cd = sf::seconds(0) ): cd(_cd){}
	
		bool isReady() const
		{
			return isReady(cd);
		}
		bool isReady(sf::Time customCd) const
		{
			return _clock.getElapsedTime() > cd;
		}
		
		bool isReadyRestart()
		{
			return isReadyRestart(cd);
		}
		bool isReadyRestart(sf::Time customCd)
		{
			if (isReady(customCd))
			{
				restart();
				return true;
			}
			return false;
		}

		void restart()
		{
			_clock.restart();
		}

		sf::Time cd;
	private:
		sf::Clock _clock;
	protected:

		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}