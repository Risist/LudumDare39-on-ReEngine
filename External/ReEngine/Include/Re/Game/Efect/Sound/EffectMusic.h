#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\ResourceManager.h>


namespace Efect
{
	class Music : public Base
	{
	public:
		Music(std::vector<TsId>);

		virtual void onUpdate(sf::Time) override;

		Music* setVolume(float& vol)
		{
			for (unsigned int i = 0; i < music.size(); music[i]->setVolume(vol), i++);
			return this;
		}

		Music* setPitch(float& pitch)
		{
			for (unsigned int i = 0; i < music.size(); music[i]->setPitch(pitch), i++);
			return this;
		}

		Music* setAttenuation(float& atte)
		{
			for (unsigned int i = 0; i < music.size(); music[i]->setAttenuation(atte), i++);
			return this;
		}

		Music*  setWhenPlaying(function<bool()> play)
		{
			whenPlay = play;
			return this;
		}

	public:
		std::vector<unique_ptr<sf::Music>> music;
		function<bool()>whenPlay;
		unsigned int toPlay;
	};
}
