#include "TurnManager.h"

TurnManager::TurnManager()
{
}

User TurnManager::GetUserTurn()
{
	return TurnManager::m_Turn;
}

void TurnManager::SetUserTurn(User Turn)
{
	TurnManager::m_Turn = Turn;
}

void TurnManager::FlipTurn()
{
	if (TurnManager::m_Turn == User::Player)
	{
		TurnManager::m_PlayerTimerPermanent += TurnManager::m_Clock.getElapsedTime().asSeconds();
		TurnManager::m_Turn = User::AI;
	}
	else
	{
		TurnManager::m_AITimerPermanent += TurnManager::m_Clock.getElapsedTime().asSeconds();
		TurnManager::m_Turn = User::Player;
	}
	TurnManager::m_Clock.restart();
}

bool TurnManager::GetGameOverStatus()
{
	return TurnManager::m_GameOver;
}

void TurnManager::SetGameOverStatus(bool GameOver)
{
	TurnManager::m_GameOver = GameOver;
}

void TurnManager::FlipGameOverStatus()
{
	if (TurnManager::m_GameOver)
	{
		TurnManager::m_GameOver = false;
	}
	else
	{
		TurnManager::m_GameOver = true;
	}
}

User TurnManager::m_Turn = User::Player;
bool TurnManager::m_GameOver = false;
float TurnManager::m_AITimerPermanent = 0.0f;
float TurnManager::m_PlayerTimerPermanent = 0.0f;
sf::Clock TurnManager::m_Clock;