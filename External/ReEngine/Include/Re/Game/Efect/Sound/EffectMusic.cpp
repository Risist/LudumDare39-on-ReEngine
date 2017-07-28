#include <Re\Game\Efect\Sound\EffectMusic.h>

namespace Efect
{
	Music::Music(std::vector<TsId> soundId)
	{
		toPlay = 0;
		for (unsigned int i = 0; i < soundId.size(); i++)
		{
			music.push_back(unique_ptr<sf::Music>(new sf::Music));
			music.back()->openFromFile(musicInst[soundId[i]]);
		}
		music.front()->play();
	}

	void Music::onUpdate(sf::Time)
	{
		if (whenPlay())
		{
			if (music[toPlay]->getStatus() == sf::SoundStream::Playing)
				return;
			else// when playing music is over or when music was stopped
			{
				if (toPlay < (music.size()-1))
				{
					toPlay++;
					music[toPlay]->play();
				}
				else
				{
					toPlay = 0;
					music[toPlay]->play();
				}
			}
		}
		else
		{
			if (music[toPlay]->getStatus() == sf::SoundStream::Status::Playing)music[toPlay]->stop();
		}
	}
}