#include "AIBoard.h"

AIBoard::AIBoard(int BoardPositionX, int BoardPositionY, int Size) : Board(BoardPositionX, BoardPositionY, Size)
{
}

// Draw the tiles
void AIBoard::Update(sf::RenderWindow* window, sf::Event event)
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
	if (MouseIntersect::Intersects(this->GetPosition(), this->GetSize(), sf::Mouse::getPosition(*window)))
	{
		int TilePositionX = (sf::Mouse::getPosition(*window).y - this->GetPosition().y) / (this->GetSize().x / 10);
		int TilePositionY = (sf::Mouse::getPosition(*window).x - this->GetPosition().x) / (this->GetSize().y / 10);
		// Update tile for each frame when mouse intersects
		if (MouseIntersect::Intersects(this->m_Board[TilePositionX][TilePositionY].getPosition()
			, sf::Vector2f(this->GetSize().x / 10, this->GetSize().y / 10), sf::Mouse::getPosition(*window)))
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
	// Check if all ships are completely destroyed
	bool AllShipsDestroyed = true;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((this->m_HiddenBoard[i][j] != PositionStateHidden::False
				&& this->m_BoardVisible[i][j] == PositionStateVisible::Intact)
				|| (this->m_HiddenBoard[i][j] != PositionStateHidden::False
					&& this->m_BoardVisible[i][j] == PositionStateVisible::Blank))
			{
				AllShipsDestroyed = false & AllShipsDestroyed;
			}
		}
	}
	if(AllShipsDestroyed) TurnManager::SetGameOverStatus(AllShipsDestroyed);
}

// Reveal visible tile status
void AIBoard::RevealTile(int x, int y)
{
	//	Stop if tile to be revealed is not blank
	if (this->m_BoardVisible[x][y] != PositionStateVisible::Blank)
	{
		if (TurnManager::GetUserTurn() == User::AI || this->m_BoardVisible[x][y] != PositionStateVisible::Intact)
		{
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
	TurnManager::FlipTurn();
}