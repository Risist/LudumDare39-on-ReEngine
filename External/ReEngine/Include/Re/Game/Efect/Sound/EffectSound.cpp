#include <Re\Game\Efect\Sound\EffectSound.h>

namespace Efect
{
	Sound::Sound(TsId soundId)
	{
		sound.setBuffer(soundInst[soundId]);
	}

	void Sound::onUpdate(sf::Time)
	{
		if (whenPlay())
		{
			if (sound.getStatus() != sf::SoundSource::Status::Playing)sound.play();
		}
		else
		{
			//if (sound.getStatus() == sf::SoundSource::Status::Playing)sound.stop();
		}

		//else sound.stop();
	}
}