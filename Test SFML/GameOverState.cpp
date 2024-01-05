#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow* window, User Winner) : m_Window(window), m_Paused(false), m_Restart(false)
{
	this->m_SegoeUIFont = FontManager::GetFont("fonts/segoeui.ttf");
	sf::Vector2f position;

	// Game over text
	if (Winner == User::AI) this->m_GameOverText.setString("You Won!");
	else this->m_GameOverText.setString("You Lost.");
	this->m_GameOverText.setFont(this->m_SegoeUIFont);
	this->m_GameOverText.setCharacterSize(40);
	position.x = (this->m_Window->getSize().x / 2) - (this->m_GameOverText.getLocalBounds().width / 2);
	position.y = this->m_Window->getSize().y * 30 / 100;
	this->m_GameOverText.setPosition(position);
	this->m_GameOverText.setFillColor(sf::Color::Black);

	// Restart rect
	this->m_RestartRect.setSize(sf::Vector2f(300, 100));
	position.x = (this->m_Window->getSize().x / 2) - (this->m_RestartRect.getLocalBounds().width / 2);
	position.y = this->m_Window->getSize().x * 40 / 100;
	this->m_RestartRect.setPosition(position);
	this->m_RestartRect.setFillColor(sf::Color(153, 217, 234, 255));

	// Restart text
	this->m_RestartText.setString("Play again");
	this->m_RestartText.setFont(this->m_SegoeUIFont);
	this->m_RestartText.setCharacterSize(40);
	position.x = (this->m_Window->getSize().x / 2) - (this->m_RestartText.getLocalBounds().width / 2);
	position.y = (this->m_Window->getSize().x * 40 / 100) + (this->m_RestartRect.getSize().y / 2)
		- (this->m_RestartText.getLocalBounds().height / 2) - 5;
	this->m_RestartText.setPosition(position);
	this->m_RestartText.setFillColor(sf::Color::Black);
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
		// Restart game -> pop GameState
		if (event.type == sf::Event::MouseButtonReleased && MouseIntersect::Intersects(this->m_RestartRect.getPosition()
			, this->m_RestartRect.getSize(), sf::Mouse::getPosition(*this->m_Window)))
		{
			this->m_Restart = true;
		}
	}
}

void GameOverState::Update()
{
	if (this->m_Paused) return;
	// Reactive button
	if (MouseIntersect::Intersects(this->m_RestartRect.getPosition(),
		this->m_RestartRect.getSize(), sf::Mouse::getPosition(*this->m_Window)))
	{
		this->m_RestartRect.setFillColor(sf::Color(167, 228, 242, 255));
		this->m_RestartRect.setOutlineThickness(5.0f);
		this->m_RestartRect.setOutlineColor(sf::Color::Black);
	}
	else
	{
		this->m_RestartRect.setFillColor(sf::Color(153, 217, 234, 255));
		this->m_RestartRect.setOutlineThickness(0.0f);
	}

	// Update state
	if (this->m_Restart)
	{
		StateManager::AddState(std::make_unique<MainMenuState>(this->m_Window));
		this->m_Restart = false;
	}
}

void GameOverState::Draw()
{
	this->m_Window->clear(sf::Color(53, 201, 242, 255));
	this->m_Window->draw(this->m_GameOverText);
	this->m_Window->draw(this->m_RestartRect);
	this->m_Window->draw(this->m_RestartText);
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
