#pragma once
#include <unordered_map>
#include <iostream>
#include "SFML/Graphics.hpp"

class FontManager
{
public:
	// Initializ all fonts
	FontManager();

	// Return reference of a font already initialized in static class
	static sf::Font GetFont(std::string FileName);
	// Empty all initialized fonts
	static void ClearFonts();

private:
	static std::unordered_map <std::string, sf::Font> m_FontMap;
};

