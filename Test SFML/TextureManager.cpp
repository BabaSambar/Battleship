#include "TextureManager.h"

TextureManager::TextureManager()
{
}

sf::Texture& TextureManager::GetTexture(std::string FileName)
{
	if (m_TextureMap.find(FileName) == m_TextureMap.end())
	{
		sf::Texture texture;
		if (texture.loadFromFile(FileName))
		{
			m_TextureMap[FileName] = texture;
		}
		else
		{
			std::cout << "Cannot load texture: " << FileName << "\n";
		}
	}
	return m_TextureMap[FileName];
}

void TextureManager::ClearTextures()
{
	m_TextureMap.clear();
}

std::unordered_map <std::string, sf::Texture> TextureManager::m_TextureMap;