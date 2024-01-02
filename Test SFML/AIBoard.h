#pragma once
#include "Board.h"
class AIBoard : public Board
{
public:
	// Board of m_Size x m_Size pixels
	AIBoard(int PositionX, int PositionY, int Size);

	// Draw each tile
	void Update(sf::RenderWindow* window, sf::Event event);

	// Reveal visible tile status
	void RevealTile(int TilePositionX, int TilePositionY);
};

