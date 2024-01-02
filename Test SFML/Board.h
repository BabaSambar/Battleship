#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <map>

#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "MouseIntersect.h"
#include "PositionState.h"
#include "TurnManager.h"

// Board class called in Game Loop
class Board
{
public:
	int m_UserPoints;
	// Board of Size x Size pixels
	Board(int BoardPositionX, int BoardPositionY, int Size);


	// Return display board class position relative to window
	sf::Vector2f GetPosition();
	// Return display board size
	sf::Vector2f GetSize();

	// Display hidden and visible board structure
	void CoutBoardStructure();

	// Board to display on screen, public for access through state class
	sf::RectangleShape m_Board[10][10];

	int m_ShipCount;
	// [Intact, Destroying, Destroyed]
	std::map<PositionStateHidden, std::vector<sf::Texture*>> TextureMap;

	// Values with reference to window
	int m_BoardPositionX, m_BoardPositionY, m_BoardSize;
	// Change board according to player and AI operations
	PositionStateVisible m_BoardVisible[10][10];
	// Stays constant after ships are initialized
	PositionStateHidden m_HiddenBoard[10][10];
	// Place a ship on hidden board structure
	bool PlaceShip(int ShipLength);
};
