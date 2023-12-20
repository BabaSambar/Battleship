#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <map>

#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "MouseIntersect.h"
#include "PositionState.h"

// Flags for user identification
enum class User : int
{
	Player = 0,
	AI = 1
};


// Flags for display status
enum class BoardDisplayState: int
{
	Disabled = 0,
	Enabled = 1
};

// Board class called in Game Loop
class Board
{
public:
	// Board of Size x Size pixels
	Board(int PositionX, int PositionY, int Size, User user=User::Player);

	// Draw each tile
	void Draw(sf::RenderWindow& window, sf::Event event, sf::Vector2i MousePosition = sf::Vector2i(0, 0), bool YourTurn = false);
	// Check if mouse button is clicked on tile
	void OnMouseClick(sf::Vector2i MousePosition);

	// Return display board class position relative to window
	sf::Vector2f GetPosition();
	// Return display board size
	sf::Vector2f GetSize();

	// Display hidden and visible board structure
	void CoutBoardStructure();
	// Reveal visible tile status
	void RevealTile(int TilePositionX, int TilePositionY);

private:

	// Board to display on screen
	sf::RectangleShape m_Board[10][10];
	User m_User;

	int ShipCount = 1;
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

