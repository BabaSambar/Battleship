#include "FontManager.h"

FontManager::FontManager()
{
}

sf::Font FontManager::GetFont(std::string FileName)
{
	if (m_FontMap.find(FileName) == m_FontMap.end())
	{
		sf::Font font;
		if (font.loadFromFile(FileName))
		{
			m_FontMap[FileName] = font;
		}
		else
		{
			std::cout << "Cannot load font: " << FileName << "\n";
		}
	}
	return m_FontMap[FileName];
}

void FontManager::ClearFonts()
{
	m_FontMap.clear();
}

std::unordered_map <std::string, sf::Font> FontManager::m_FontMap;