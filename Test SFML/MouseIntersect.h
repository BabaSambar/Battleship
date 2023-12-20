#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class MouseIntersect
{
public:
	static bool Intersects(sf::Vector2f ObjectPosition, sf::Vector2f ObjectSize, sf::Vector2i MousePosition);
};
