#include "MouseIntersect.h"


bool MouseIntersect::Intersects(sf::Vector2f ObjectPosition,
	sf::Vector2f ObjectSize, sf::Vector2i MousePosition)
{
	sf::FloatRect objectOutline(ObjectPosition, ObjectSize);
	return objectOutline.contains(static_cast<sf::Vector2f>(MousePosition));
}
