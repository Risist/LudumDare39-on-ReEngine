#include <Re\Graphics\ResourceManager.h>

Image ResourceManager::im;
Color ResourceManager::clTransparent(255, 255, 255);

ResourceManager res;

ResourceManager::ResourceManager()
{
}

void ResourceManager::createTexture(Texture& ts, const std::string & path)
{
	if (im.loadFromFile(path))
	{
		im.createMaskFromColor(clTransparent);
		ts.loadFromImage(im);
	}
	else
	{
		std::cout << "Failed to open the atlas: \"" << path << "\"" << std::endl;
	}
}

string ResourceManager::createTranscription(const std::string & path)
{
	fstream file(path);
	string s;
	char c;
	while (file>>c)
	{
		s.push_back(c);
	}

	return s;
}

void ResourceManager::serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const
{
	// does not save resources
}
void ResourceManager::deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
{
	// heder line
	std::string prepathGraphics = loader.loadRaw("prepathGraphics", "");
	std::string prepathFont = loader.loadRaw("prepathFont", "");
	std::string prepathSound = loader.loadRaw("prepathSound", "");
	std::string prepathScript = loader.loadRaw("prepathScript", "");
	std::string prepathResource = loader.loadRaw("prepathResource", "");

	/// 0 index always means empty resource
	res.atlases[0] = Texture();
	res.textures[0] = TextureInstance();
	res.fonts[0] = Font();
	res.cashedScript[0] = string();
	res.sounds[0] = sf::SoundBuffer();

	DATA_SCRIPT_MULTILINE(file, loader)
	{
		string type = loader.load<string>("type", "UNKNOWN");

		/// load texture from file
		if (type == "atlas")
		{
			std::string path = prepathGraphics + loader.loadRaw("path", "non_written_path_error");

			ResId atlasId = loader.load("atlasId", 0u);
			ResId textureId = loader.load("textureId", atlasId);

			if (path == prepathGraphics + "non_written_path_error")
			{
				cerr << "ResourceManager: in type = " << type << "; path = " << path << "\n";
			}else
			if (atlasId != 0u)
			{
				createTexture(atlases[atlasId], path);
				if (textureId != 0u)
				{
					textures[textureId].bounds.width = atlases[atlasId].getSize().x;
					textures[textureId].bounds.height = atlases[atlasId].getSize().y;
					textures[textureId].atlasId = atlasId;
				}
			}
			else
			{
				cerr << "ResourceManager: in " << type << "; atlas id not set up\n";
			}
		}
		/// set up texture bounds for one texture placed in atlas
		else if (type == "textureSingle")
		{
			ResId atlasId = loader.load("atlasId", 0u);

			/// id from which texture instances will be added
			ResId textureId = loader.load("textureId", 0u);


			if (atlasId != 0u && textureId != 0u)
			{
				textures[textureId].bounds.left = loader.load("posX", 0u);
				textures[textureId].bounds.top = loader.load("posY", 0u);

				textures[textureId].bounds.width = loader.load("width", atlases[atlasId].getSize().x);
				textures[textureId].bounds.height = loader.load("height", atlases[atlasId].getSize().y);

				textures[textureId].atlasId = atlasId;
			}
			else
			{
				cerr << "ResourceManager: in " << type << "; atlas or texture id not set up\n";
			}

		}
		/// set up texture bounds with constant grid
		/// its like every picture in texture has the same size
		else if (type == "textureGridX")
		{
			ResId atlasId = loader.load("atlasId", 0u);

			/// id from which texture instances will be added
			ResId textureId = loader.load("textureFromId", 0u);

			size_t n = loader.load("n", 1u);

			if (atlasId && textureId != 0u)
			{
				unsigned int posX = loader.load("posX", 0u);
				unsigned int posY = loader.load("posY", 0u);

				const unsigned int w = loader.load("width", 0u);
				const unsigned int h = loader.load("height", 0u);

				for (int i = 0; i < n; ++i)
				{
					textures[textureId].bounds.left = posX;
					textures[textureId].bounds.top = posY;
					posX += w;
					//posY += h;

					textures[textureId].bounds.width = w;
					textures[textureId].bounds.height = h;
				}
				textures[textureId].atlasId = atlasId;
			}
			else
			{
				cerr << "ResourceManager: in " << type << " atlas or texture id not set up\n";
			}
		}
		else if (type == "textureGridY")
		{
			ResId atlasId = loader.load("atlasId", 0u);

			/// id from which texture instances will be added
			ResId textureId = loader.load("textureFromId", 0u);

			size_t n = loader.load("n", 1u);

			if (atlasId && textureId != 0u)
			{
				unsigned int posX = loader.load("posX", 0u);
				unsigned int posY = loader.load("posY", 0u);

				const unsigned int w = loader.load("width", 0u);
				const unsigned int h = loader.load("height", 0u);

				for (int i = 0; i < n; ++i)
				{
					textures[textureId].bounds.left = posX;
					textures[textureId].bounds.top = posY;
					//posX += w;
					posY += h;

					textures[textureId].bounds.width = w;
					textures[textureId].bounds.height = h;
				}
				textures[textureId].atlasId = atlasId;
			}
			else
			{
				cerr << "ResourceManager: in " << type << " atlas or texture id not set up\n";
			}
		}
		/// cashe scripts in memory for faster loading
		else if (type == "script")
		{
			std::string path = prepathScript + loader.loadRaw("path", "non_written_path_error");
			ResId id = loader.load("id", 0u);
			if (id == 0u)
				cerr << "RespurceManager: in " << type << "id not set or set to 0\n";
			else
			{
				cashedScript[id] = createTranscription(path);
			}
		}
		/// load sounds from files
		else if (type == "sound")
		{
			std::string path = prepathSound + loader.loadRaw("path", "non_written_path_error");

			ResId id = loader.load("id", 0u);
			if (id == 0u)
				std::cerr << "ResourceManager: in type = " << type << 
					"; id = nonon_named\n"
					"\tPath = " << path << "\n";


			sounds[id].loadFromFile(path);
		}
		/// load fonts from files
		else if (type == "font")
		{
			std::string path = prepathFont + loader.loadRaw("path", "non_written_path_error");

			ResId id = loader.load("id", 0u);
			if (id == 0u)
				std::cerr << "ResourceManager: in type = " << type << "; id = nonon_named\n"
					"\tPath = " << path << "\n";


			fonts[id].loadFromFile(path);
		}
		/// load resources from another file similar to this
		else if (type == "resource")
		{
			std::string path = prepathFont + loader.loadRaw("path", "non_written_path_error");

			deserialise(path);
		}
		else
		{
			std::cerr << "ResourceManager: in type = undefined\n";
		}
	}
	
}

Texture * ResourceManager::TextureInstance::getTexture() const
{
	return &atlasInst[atlasId];
}
