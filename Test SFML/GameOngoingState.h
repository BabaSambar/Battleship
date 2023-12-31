#pragma once
#include "GameState.h"

#include "StateManager.h"
#include "MouseIntersect.h"
#include "FontManager.h"
#include "Board.h"
#include "TurnManager.h"

class GameOngoingState : public GameState
{
public:
	GameOngoingState(sf::RenderWindow* window);

	void HandleEvents();
	void Update();
	void Draw();

	void Start();
	void Pause();

private:
	bool m_Paused;
	bool m_GameOver;
	bool m_StartTimer;

	sf::RenderWindow* m_Window;
	// Font for all texts

	sf::Font m_SegoeUIFont;
	// Player board
	Board m_PlayerBoard;
	// AI board
	Board m_AIBoard;

	// Player turn card
	sf::RectangleShape m_PlayerTurnRect;
	// AI turn card
	sf::RectangleShape m_AITurnRect;

	// Points text
	sf::Text m_PointsText;
	// Player points text
	sf::Text m_PlayerPointsText;
	// AI points text
	sf::Text m_AIPointsText;

	// Player time
	float m_PlayerTimer;
	sf::Text m_PlayerTimeText;
	// AI time
	float m_AITimer;
	sf::Text m_AITimeText;
};

