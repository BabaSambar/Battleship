#include "GameOngoingState.h"

GameOngoingState::GameOngoingState(sf::RenderWindow* window) : m_Paused(false), m_Window(window)
	, m_PlayerBoard(0, 100, 500, User::Player), m_AIBoard(550, 100, 500, User::AI), m_StartTimer(false), m_GameOver(false)
{
	sf::Vector2f position;
	// Font
	this->m_SegoeUIFont = FontManager::GetFont("fonts/segoeui.ttf");

	// Handle user turns and time
	TurnManager::m_Clock.restart();
	this->m_PlayerTimer = 0.0f;
	this->m_AITimer = 0.0f;

	// Player timer
	this->m_PlayerTimeText.setString(std::to_string(this->m_PlayerTimer));
	this->m_PlayerTimeText.setFont(this->m_SegoeUIFont);
	this->m_PlayerTimeText.setCharacterSize(30);
	position.x = this->m_PlayerBoard.GetPosition().x + 10;
	position.y = 10;
	this->m_PlayerTimeText.setPosition(position);
	this->m_PlayerTimeText.setFillColor(sf::Color::Black);

	// AI timer
	this->m_AITimeText.setString(std::to_string(this->m_AITimer));
	this->m_AITimeText.setFont(this->m_SegoeUIFont);
	this->m_AITimeText.setCharacterSize(30);
	position.x = this->m_AIBoard.GetPosition().x + this->m_AIBoard.GetSize().x
		- this->m_AITimeText.getLocalBounds().width - 20;
	position.y = 10;
	this->m_AITimeText.setPosition(position);
	this->m_AITimeText.setFillColor(sf::Color::Black);

	// Common points text
	this->m_PointsText.setString("Points");
	this->m_PointsText.setFont(this->m_SegoeUIFont);
	this->m_PointsText.setCharacterSize(40);
	position.x = (this->m_Window->getSize().x / 2) - (this->m_PointsText.getLocalBounds().width / 2);
	position.y = 10;
	this->m_PointsText.setPosition(position);
	this->m_PointsText.setFillColor(sf::Color::Black);

	// Player points text
	this->m_PlayerPointsText.setString(std::to_string(this->m_PlayerBoard.m_UserPoints));
	this->m_PlayerPointsText.setFont(this->m_SegoeUIFont);
	this->m_PlayerPointsText.setCharacterSize(40);
	position.x = this->m_AIBoard.GetPosition().x;
	position.y = this->m_PlayerBoard.GetPosition().y - this->m_PlayerPointsText.getLocalBounds().height - 20;
	this->m_PlayerPointsText.setPosition(position);
	this->m_PlayerPointsText.setFillColor(sf::Color::Black);

	// AI points text
	this->m_AIPointsText.setString(std::to_string(this->m_AIBoard.m_UserPoints));
	this->m_AIPointsText.setFont(this->m_SegoeUIFont);
	this->m_AIPointsText.setCharacterSize(40);
	position.x = this->m_PlayerBoard.GetPosition().x + this->m_PlayerBoard.GetSize().x
		- this->m_PlayerPointsText.getLocalBounds().width;
	position.y = this->m_PlayerBoard.GetPosition().y - this->m_PlayerPointsText.getLocalBounds().height - 20;
	this->m_AIPointsText.setPosition(position);
	this->m_AIPointsText.setFillColor(sf::Color::Black);
}

void GameOngoingState::HandleEvents()
{
	if (this->m_Paused) return;
	sf::Event event;
	while (this->m_Window->pollEvent(event))
	{
		// Close window
		if (event.type == sf::Event::Closed)
		{
			this->m_Window->close();
		}
		// Start the timer after player plays first move
		if (event.mouseButton.button == sf::Mouse::Left) this->m_StartTimer = true;

		this->m_PlayerBoard.Update(m_Window, event);
		this->m_AIBoard.Update(m_Window, event);
	
		if (TurnManager::GetGameOverStatus())
		{
			this->m_GameOver = true;
		}
		else
		{
			this->m_GameOver = false;
		}
	}
}

void GameOngoingState::Update()
{
	if (this->m_Paused) return;

	sf::Vector2f position;
	// Update player points
	this->m_PlayerPointsText.setString(std::to_string(this->m_PlayerBoard.m_UserPoints));
	position.x = this->m_AIBoard.GetPosition().x;
	position.y = this->m_PlayerBoard.GetPosition().y - this->m_PlayerPointsText.getLocalBounds().height - 20;

	this->m_PlayerPointsText.setPosition(position);
	// Update AI points
	this->m_AIPointsText.setString(std::to_string(this->m_AIBoard.m_UserPoints));
	position.x = this->m_PlayerBoard.GetPosition().x + this->m_PlayerBoard.GetSize().x
		- this->m_PlayerPointsText.getLocalBounds().width;
	position.y = this->m_PlayerBoard.GetPosition().y - this->m_PlayerPointsText.getLocalBounds().height - 20;
	this->m_AIPointsText.setPosition(position);

	if (!this->m_StartTimer) return;
	if (TurnManager::GetUserTurn() == User::Player)
	{
		// Update player time
		this->m_PlayerTimer = TurnManager::m_PlayerTimerPermanent + TurnManager::m_Clock.getElapsedTime().asSeconds();
		this->m_PlayerTimeText.setString(std::to_string(this->m_PlayerTimer));

		this->m_AITimer = TurnManager::m_AITimerPermanent;
		this->m_AITimeText.setString(std::to_string(this->m_AITimer));
	}
	else if (TurnManager::GetUserTurn() == User::AI)
	{
		// Update AI time
		this->m_AITimer = TurnManager::m_AITimerPermanent + TurnManager::m_Clock.getElapsedTime().asSeconds();
		this->m_AITimeText.setString(std::to_string(this->m_AITimer));

		this->m_PlayerTimer = TurnManager::m_PlayerTimerPermanent;
		this->m_PlayerTimeText.setString(std::to_string(this->m_PlayerTimer));
	}

	if (this->m_GameOver)
	{
		std::cout << "Game's over\n";
		//StateManager::AddState(std::make_unique<GameOverState>());
	}
}

void GameOngoingState::Draw()
{
	this->m_Window->clear(sf::Color(53, 201, 242, 255));
	// Draw tiles of board
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->m_Window->draw(this->m_PlayerBoard.m_Board[i][j]);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->m_Window->draw(this->m_AIBoard.m_Board[i][j]);
		}
	}
	// Draw points text and timer
	this->m_Window->draw(m_PointsText);
	this->m_Window->draw(m_PlayerPointsText);
	this->m_Window->draw(m_AIPointsText);
	this->m_Window->draw(m_PlayerTimeText);
	this->m_Window->draw(m_AITimeText);
	this->m_Window->display();
}

void GameOngoingState::Start()
{
	this->m_Paused = false;
}

void GameOngoingState::Pause()
{
	this->m_Paused = true;
}
