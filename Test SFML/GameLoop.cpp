#include "GameLoop.h"

// Start game from main menu state
GameLoop::GameLoop()
{
	srand(time(0));
	m_Window.create(sf::VideoMode(1050, 650), "Battleship", sf::Style::Close);
	m_Window.setFramerateLimit(60);
	m_Window.setKeyRepeatEnabled(false);
	StateManager::AddState(std::make_unique<MainMenuState>(&m_Window));
}

// Include all game logic here
void GameLoop::Run()
{
	while (m_Window.isOpen())
	{
		StateManager::ProcessChanges();
		if (!StateManager::Empty())
		{
			StateManager::GetTopState()->HandleEvents();
			StateManager::GetTopState()->Update();
			StateManager::GetTopState()->Draw();
		}
		else
		{
			m_Window.close();
		}
	}
}
