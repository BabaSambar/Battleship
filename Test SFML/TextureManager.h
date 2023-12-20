#pragma once
#include <unordered_map>
#include <iostream>
#include "SFML/Graphics.hpp"

class TextureManager
{
public:
	// Initializ all textures
	TextureManager();

	// Return address of a texture already initialized in static class
	static sf::Texture& GetTexture(std::string FileName);
	// Empty all initialized textures
	static void ClearTextures();

private:
	static std::unordered_map <std::string, sf::Texture> m_TextureMap;
};

