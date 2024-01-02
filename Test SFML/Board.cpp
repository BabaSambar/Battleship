#include "Board.h"

// Return a random (not really) ship texture for initialization
std::vector<sf::Texture*> GetRandomShipTexture()
{
	std::vector<sf::Texture*> Textures;
	int RandomNumber = rand() % 5;
	switch (RandomNumber)
	{
	case 0:
		Textures.push_back(&TextureManager::GetTexture("res/whiteship.png"));
		Textures.push_back(&TextureManager::GetTexture("res/whiteship_destroying.png"));
		Textures.push_back(&TextureManager::GetTexture("res/whiteship_destroyed.png"));
		break;
	case 1:
		Textures.push_back(&TextureManager::GetTexture("res/greenship.png"));
		Textures.push_back(&TextureManager::GetTexture("res/greenship_destroying.png"));
		Textures.push_back(&TextureManager::GetTexture("res/greenship_destroyed.png"));
		break;
	case 2:
		Textures.push_back(&TextureManager::GetTexture("res/purpleship.png"));
		Textures.push_back(&TextureManager::GetTexture("res/purpleship_destroying.png"));
		Textures.push_back(&TextureManager::GetTexture("res/purpleship_destroyed.png"));
		break;
	case 3:
		Textures.push_back(&TextureManager::GetTexture("res/redship.png"));
		Textures.push_back(&TextureManager::GetTexture("res/redship_destroying.png"));
		Textures.push_back(&TextureManager::GetTexture("res/redship_destroyed.png"));
		break;
	case 4:
		Textures.push_back(&TextureManager::GetTexture("res/yellowship.png"));
		Textures.push_back(&TextureManager::GetTexture("res/yellowship_destroying.png"));
		Textures.push_back(&TextureManager::GetTexture("res/yellowship_destroyed.png"));
		break;
	default:
		break;
	}
	return Textures;
}

// Set a ship in board structure
bool Board::PlaceShip(int ShipLength)
{
	// Set ship starting position and orientation
	int orientation = rand() % 2;
	int startRow = 0, startCol = 0;
	PositionStateHidden ShipIndex = static_cast<PositionStateHidden>(this->m_ShipCount);
	if (orientation == 0)  // 0 = Horizontal
	{
		startRow = rand() % 10;
		startCol = rand() % (10 - ShipLength);
	}
	else  // 1 = Vertical
	{
		startRow = rand() % (10 - ShipLength);
		startCol = rand() % 10;
	}

	// Prevent ship overlap by returning false for each overlap by returning if tile already placed
	for (int i = 0; i < ShipLength; i++)
	{
		if (orientation == 1)
		{
			if (this->m_HiddenBoard[startRow + i][startCol] != PositionStateHidden::False)
			{
				return false;
			}
		}
		else
		{
			if (this->m_HiddenBoard[startRow][startCol + i] != PositionStateHidden::False)
			{
				return false;
			}
		}
	}
	for (int i = 0; i < ShipLength;i++)
	{
		if (orientation == 1)
		{
			this->m_HiddenBoard[startRow + i][startCol] = ShipIndex;
		}
		else
		{
			this->m_HiddenBoard[startRow][startCol + i] = ShipIndex;
		}
	}
	this->m_ShipCount++;
	return true;
}

// Initialize tile sizes and positions
Board::Board(int BoardPositionX, int BoardPositionY, int Size) : m_UserPoints(0), m_ShipCount(1),
m_BoardPositionX(BoardPositionX), m_BoardPositionY(BoardPositionY), m_BoardSize(Size)
{
	// Set default value for visible and hidden board
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->m_BoardVisible[i][j] = PositionStateVisible::Blank;
			this->m_HiddenBoard[i][j] = PositionStateHidden::False;
		}
	}

	// Place 5,4,3,3,2 length ships
	while (!this->PlaceShip(5));
	while (!this->PlaceShip(4));
	while (!this->PlaceShip(3));
	while (!this->PlaceShip(3));
	while (!this->PlaceShip(2));

	// Set display board texture
	int TileSize = Size / 10;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->m_Board[i][j].setSize(sf::Vector2f(TileSize, TileSize));
			this->m_Board[i][j].setPosition(sf::Vector2f(BoardPositionX + (j * TileSize)
				, BoardPositionY + (i * TileSize)));
			this->m_Board[i][j].setTexture(&TextureManager::GetTexture("res/water.png"));
		}
	}

	// Load ship intact, destroying and destroyed textures
	PositionStateHidden ShipIndex;
	for (int i = 1; i <= 5; i++)
	{
		ShipIndex = static_cast<PositionStateHidden>(i);
		this->TextureMap[ShipIndex] = GetRandomShipTexture();
	}
}

sf::Vector2f Board::GetPosition()
{
	return sf::Vector2f(this->m_BoardPositionX, this->m_BoardPositionY);
}

sf::Vector2f Board::GetSize()
{
	return sf::Vector2f(this->m_BoardSize, this->m_BoardSize);
}

// Display Visible and Hidden Board Structure
void Board::CoutBoardStructure()
{
	// Visible Board
	std::cout << "Visible Board:\n";
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << static_cast<int>(this->m_BoardVisible[i][j]) << ", ";
		}
		std::cout << "\n";
	}
	// Hidden Board
	std::cout << "Hidden Board:\n";
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << static_cast<int>(this->m_HiddenBoard[i][j]) << ", ";
		}
		std::cout << "\n";
	}
}
