#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow* window) : m_Window(window), m_Paused(false)
{
	this->rect.setPosition(sf::Vector2f(50, 50));
	this->rect.setSize(sf::Vector2f(100, 100));
	this->rect.setFillColor(sf::Color::Cyan);
}

void GameOverState::HandleEvents()
{
	sf::Event event;
	while (this->m_Window->pollEvent(event))
	{
		// Close window
		if (event.type == sf::Event::Closed)
		{
			this->m_Window->close();
		}
	}
}

void GameOverState::Update()
{
}

void GameOverState::Draw()
{
	this->m_Window->clear(sf::Color::White);
	this->m_Window->draw(this->rect);
	this->m_Window->display();
}

void GameOverState::Start()
{
	this->m_Paused = false;
}

void GameOverState::Pause()
{
	this->m_Paused = true;
}
