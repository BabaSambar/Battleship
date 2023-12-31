#include "Board.h"

// Return a ship texture for initialization
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
	PositionStateHidden ShipIndex = static_cast<PositionStateHidden>(this->ShipCount);
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
	this->ShipCount++;
	return true;
}

// Initialize tile sizes and positions
Board::Board(int BoardPositionX, int BoardPositionY, int Size, User User)
{
	// Debug
	this->x = 0;
	this->y = 0;

	this->m_User = User;
	this->m_UserPoints = 0;
	this->m_UserTurn = false;
	this->m_BoardPositionX = BoardPositionX;
	this->m_BoardPositionY = BoardPositionY;
	this->m_BoardSize = Size;
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
	// Set ship textures if user is player, else keep ships hidden
	if (User == User::Player)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (this->m_HiddenBoard[i][j] != PositionStateHidden::False)
				{
					this->m_Board[i][j].setTexture((this->TextureMap[this->m_HiddenBoard[i][j]])[0]);
					this->m_BoardVisible[i][j] = PositionStateVisible::Intact;
				}
			}
		}
	}
}

// Draw the tiles
void Board::Update(sf::RenderWindow* window, sf::Event event)
{
	// Update the display board
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sf::Vector2i Position(i, j);
			// If tile is intact
			if (this->m_BoardVisible[i][j] == PositionStateVisible::Intact
				&& this->m_HiddenBoard[i][j] != PositionStateHidden::False)
			{
				sf::Texture* ShipTexture = this->TextureMap[this->m_HiddenBoard[i][j]][0];
				this->m_Board[i][j].setTexture(ShipTexture);
			}
			// If tile is destroying
			else if (this->m_BoardVisible[i][j] == PositionStateVisible::Destroying 
				&& this->m_HiddenBoard[i][j] != PositionStateHidden::False)
			{
				sf::Texture* ShipTexture = this->TextureMap[this->m_HiddenBoard[i][j]][1];
				this->m_Board[i][j].setTexture(ShipTexture);
			}
			// If tile is destroyed
			else if (this->m_BoardVisible[i][j] == PositionStateVisible::Destroyed)
			{
				sf::Texture* ShipTexture = this->TextureMap[this->m_HiddenBoard[i][j]][2];
				this->m_Board[i][j].setTexture(ShipTexture);
			}
			// If tile is revealed water
			else if (this->m_BoardVisible[i][j] == PositionStateVisible::Revealed)
			{
				this->m_Board[i][j].setTexture(&TextureManager::GetTexture("res/water_revealed.png"));
			}
		}
	}

	// Check if mouse intersects and if a tile needs to be revealed
	if (MouseIntersect::Intersects(this->GetPosition()
		, this->GetSize(), sf::Mouse::getPosition(*window)) && this->m_User == User::AI)
	{
		int TilePositionX = (sf::Mouse::getPosition(*window).y -
			this->GetPosition().y) / (this->GetSize().x / 10);
		int TilePositionY = (sf::Mouse::getPosition(*window).x -
			this->GetPosition().x) / (this->GetSize().y / 10);
		// Update tile for each frame when mouse intersects
		if (MouseIntersect::Intersects(this->m_Board[TilePositionX][TilePositionY].getPosition()
			, sf::Vector2f(this->GetSize().x / 10, this->GetSize().y / 10),
			sf::Mouse::getPosition(*window)))
		{
			this->m_Board[TilePositionX][TilePositionY].setFillColor(sf::Color(53, 201, 242, 255));
		}
		// Reset the board background color
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				// Don't reset tile color if mouse hovers over it
				if (i == TilePositionX && j == TilePositionY) continue;
				this->m_Board[i][j].setFillColor(sf::Color::White);
			}
		}
		// Reveal tile if it is clicked
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left 
			&& TurnManager::GetUserTurn() == User::Player)
		{
			if (TilePositionX <= 9 && TilePositionY <= 9)
			{
				this->RevealTile(TilePositionX, TilePositionY);
			}
		}
	}
	else if (this->m_User == User::Player && TurnManager::GetUserTurn() == User::AI)
	{
		// ADD SMART AI DECISION MAKING
		// DEBUG: TEMP SOLUTION
		this->RevealTile(this->x, this->y);
	}

	// Check if all ships are completely destroyed
	bool AllShipsDestroyed = true;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// Player board - ship is intact
			if ((this->m_HiddenBoard[i][j] != PositionStateHidden::False
				&& this->m_BoardVisible[i][j] == PositionStateVisible::Intact)
				|| (this->m_HiddenBoard[i][j] != PositionStateHidden::False
					&& this->m_BoardVisible[i][j] == PositionStateVisible::Blank))
			{
				AllShipsDestroyed = false & AllShipsDestroyed;
			}
		}
	}
	TurnManager::SetGameOverStatus(AllShipsDestroyed);
}

// Reveal visible tile status
void Board::RevealTile(int x, int y)
{
	if (this->m_User == User::Player)
	{		
		//	Stop if tile is not blank
		if (this->m_BoardVisible[x][y] != PositionStateVisible::Blank)
		{
			if (this->m_User != User::Player || this->m_BoardVisible[x][y] != PositionStateVisible::Intact)
			{
				std::cout << "invalid tile\n";
				return;
			}
		}
		// Check if tile is part of any ship
		if (this->m_HiddenBoard[x][y] != PositionStateHidden::False)
		{
			// Check if ship containing tile is completely destroyed
			PositionStateHidden TileState = this->m_HiddenBoard[x][y];
			bool ShipCompletelyDestroyed = true;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10;j++)
				{
					if (this->m_HiddenBoard[i][j] != TileState) continue;
					if (i == x && j == y) continue;
					if (this->m_BoardVisible[i][j] == PositionStateVisible::Destroying)
					{
						ShipCompletelyDestroyed = true & ShipCompletelyDestroyed;
					}
					else
					{
						ShipCompletelyDestroyed = false & ShipCompletelyDestroyed;
					}
				}
			}
			// Update the visible map
			if (ShipCompletelyDestroyed)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10;j++)
					{
						if (this->m_HiddenBoard[i][j] == TileState)
						{
							this->m_BoardVisible[i][j] = PositionStateVisible::Destroyed;
						}
					}
				}
				this->m_UserPoints += 2;
			}
			else
			{
				this->m_BoardVisible[x][y] = PositionStateVisible::Destroying;
				this->m_UserPoints++;
			}

		}
		// Tile contains water
		else
		{
			this->m_BoardVisible[x][y] = PositionStateVisible::Revealed;
		}
		// DEBUG: TEMP SOLUTION
		this->x++;
		if (this->x > 9)
		{
			this->x = 0;
			this->y++;
		}
	}
	else if(this->m_User == User::AI)
	{
		//	Stop if tile is not blank
		if (this->m_BoardVisible[x][y] != PositionStateVisible::Blank)
		{
			if (this->m_User != User::Player || this->m_BoardVisible[x][y] != PositionStateVisible::Intact)
			{
				std::cout << "invalid tile\n";
				return;
			}
		}
		// Check if tile is part of any ship
		if (this->m_HiddenBoard[x][y] != PositionStateHidden::False)
		{
			// Check if ship containing tile is completely destroyed
			PositionStateHidden TileState = this->m_HiddenBoard[x][y];
			bool ShipCompletelyDestroyed = true;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10;j++)
				{
					if (this->m_HiddenBoard[i][j] != TileState) continue;
					if (i == x && j == y) continue;
					if (this->m_BoardVisible[i][j] == PositionStateVisible::Destroying)
					{
						ShipCompletelyDestroyed = true & ShipCompletelyDestroyed;
					}
					else
					{
						ShipCompletelyDestroyed = false & ShipCompletelyDestroyed;
					}
				}
			}
			// Update the visible map
			if (ShipCompletelyDestroyed)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10;j++)
					{
						if (this->m_HiddenBoard[i][j] == TileState)
						{
							this->m_BoardVisible[i][j] = PositionStateVisible::Destroyed;
						}
					}
				}
				this->m_UserPoints += 2;
			}
			else
			{
				this->m_BoardVisible[x][y] = PositionStateVisible::Destroying;
				this->m_UserPoints++;
			}

		}
		// Tile contains water
		else
		{
			this->m_BoardVisible[x][y] = PositionStateVisible::Revealed;
		}
	}
	TurnManager::FlipTurn();
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
	std::cout << "USER: " << static_cast<int>(this->m_User) << "\n";
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
