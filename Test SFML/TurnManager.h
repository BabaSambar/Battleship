#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"

// Flags for user identification
enum class User : int
{
	Player = 0,
	AI = 1
};

class TurnManager
{
public:
	TurnManager();

	static User GetUserTurn();
	static void SetUserTurn(User Turn);
	static void FlipTurn();

	static bool GetGameOverStatus();
	static void SetGameOverStatus(bool GameOver);
	static void FlipGameOverStatus();

	// Common clock
	static sf::Clock m_Clock;
	static float m_AITimerPermanent;
	static float m_PlayerTimerPermanent;

private:
	static User m_Turn;
	static bool m_GameOver;
};

