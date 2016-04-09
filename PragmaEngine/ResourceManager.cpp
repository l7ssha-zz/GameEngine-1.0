#include "ResourceManager.h"

namespace PragmaEngine {

	TextureCache ResourceManager::_texturecache;

	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return _texturecache.getTexture(texturePath);
	}

}