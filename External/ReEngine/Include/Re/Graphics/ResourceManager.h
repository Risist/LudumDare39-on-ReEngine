#pragma once
#include <Re\Common\utility.h>
#include <string>

using namespace sf;
using namespace std;

using ResId = uint16;


/// class which contains game resources
class ResourceManager : public Res::ISerialisable
{
public:
	ResourceManager();

	/// list of loaded textures
	std::map< ResId, Texture> atlases;
	
	/// struct to hold data about texture instance placed in atlas
	struct TextureInstance
	{
		ResId atlasId;
		Texture* getTexture() const;
		void setSprite(sf::Sprite& inSp)
		{
			inSp.setTexture(*getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void setConvexShape(sf::ConvexShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void setCircleShape(sf::CircleShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void setRectShape(sf::RectangleShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}

 		sf::IntRect bounds;
	};
	std::map<ResId, TextureInstance> textures;


	std::map< ResId, Font> fonts;
	std::map< ResId, SoundBuffer> sounds;
	/// to faster load scripts many times in a row
	/// save script in memory, so disc operations is not needed
	std::map< ResId, string> cashedScript;

	void createTexture(Texture& ts, const std::string& path);
	string createTranscription(const std::string& path);

	/// set color which shoud be treated as transparent
	static inline void setClTransparent(const Color& s)
	{
		clTransparent = s;
	}
	/// get color which shoud be treated as transparent
	static inline const Color& getClTransparent()
	{
		return clTransparent;
	}

private:
	static Image im;
	static Color clTransparent;

protected:
	virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
	virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
};
extern ResourceManager res;



/// defines for easier usage
#define atlasInst res.atlases
#define tsInst res.textures
#define fontInst res.fonts
#define soundInst res.sounds
#define scriptInst res.cashedScript


