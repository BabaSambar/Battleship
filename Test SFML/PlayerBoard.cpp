#include "PlayerBoard.h"


PlayerBoard::PlayerBoard(int BoardPositionX, int BoardPositionY, int Size) : Board(BoardPositionX, BoardPositionY, Size)
{
	// DEBUG
	this->x = 0;
	this->y = 0;

	// Set ship textures
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


// Draw the tiles
void PlayerBoard::Update(sf::RenderWindow* window, sf::Event event)
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

	// Reveal tile
	// ADD SMART AI DECISION MAKING
	// DEBUG: TEMP SOLUTION
	if (TurnManager::GetUserTurn() == User::AI)
	{
		// Set default values for heatmap
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				this->m_HeatMap[i][j] = 0;
			}
		}

		// CHECK PROXIMITY FIRST!!!

		// Execute for each ship and update heatmap
		for (int i = 0; i < 5; i++)
		{
			int ShipIndex= i;
			int ShipLength;
			if (ShipIndex < 3) ShipLength = ShipIndex - 1;
			else ShipLength = ShipIndex;

			// Check if ship of ShipLength is destroyed
			bool ShipIntact = true;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (this->m_BoardVisible[i][j] == PositionStateVisible::Destroyed)
					{
						ShipIntact = false & ShipIntact;
					}
				}
			}
			if (!ShipIntact) continue;

			// Check horizontal rows to update heatmap
			for (int i = 0; i < 10; i++)
			{
				int x = 0;  // Two pointer approach for each row
				while (x < 10)
				{
					bool Proceed = true;
					// Scan
					for (int y = x; y < ShipLength; y++)
					{
						if (this->m_BoardVisible[i][y] != PositionStateVisible::Blank) x += ShipLength;
					}
					if (!Proceed) continue; x++;
					// Add to heatmap
					for (int j = 0; j < ShipLength; j++)
					{
						// WTF IS THIS WHAT AM I DOING WHY IS THIS INSIDE A WHILE LOOP WHY WHAT HOW
					}
				}
			}

		}


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
void PlayerBoard::RevealTile(int x, int y)
{
	//	Stop if tile is not blank
	if (this->m_BoardVisible[x][y] != PositionStateVisible::Blank)
	{
		if (TurnManager::GetUserTurn() == User::Player || this->m_BoardVisible[x][y] != PositionStateVisible::Intact)
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
	// DEBUG: TEMP SOLUTION
	this->x++;
	if (this->x > 9)
	{
		this->x = 0;
		this->y++;
	}
	
	TurnManager::FlipTurn();
}
