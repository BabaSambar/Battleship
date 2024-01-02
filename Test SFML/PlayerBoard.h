#pragma once
#include "Board.h"

class PlayerBoard : public Board
{
public:
	// DEBUG
	int x, y;
	// Board of m_Size x m_Size pixels
	PlayerBoard(int PositionX, int PositionY, int Size);

	// Draw each tile
	void Update(sf::RenderWindow* window, sf::Event event);

	// Reveal visible tile status
	void RevealTile(int TilePositionX, int TilePositionY);
};