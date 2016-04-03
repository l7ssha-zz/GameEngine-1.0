#include "TextureCache.h"



TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
	auto mit = _textureMap.find(texturePath);	//lookup for texture

	//check the map
	if (mit == _textureMap.end()) {
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);	//load PNG

		_textureMap.insert(make_pair(texturePath, newTexture));	//insert to MAP

		std::cout << "Texture cached" << std::endl;

		return newTexture;
	}

	std::cout << "Texture loaded from cache" << std::endl;
	return mit->second;	//return texture from cache

}
