#include "MainMenuState.h"


MainMenuState::MainMenuState(sf::RenderWindow* window) : m_Paused(false), m_StartGame(false), m_GetHelp(false), m_Window(window)
{
	sf::Vector2f position;

	// Font
	this->m_SegoeUIFont = FontManager::GetFont("fonts/segoeui.ttf");


	// Battleship heading text initialize
	this->m_HeadingText.setString("Battleship");
	this->m_HeadingText.setFont(this->m_SegoeUIFont);
	this->m_HeadingText.setCharacterSize(50);
	position.x = (this->m_Window->getSize().x / 2) - (this->m_HeadingText.getLocalBounds().width / 2);
	position.y = this->m_Window->getSize().y - (this->m_Window->getSize().y * (1 - (20.0f / 100.0f))) - (this->m_HeadingText.getLocalBounds().height / 2);
	this->m_HeadingText.setPosition(position);
	this->m_HeadingText.setFillColor(sf::Color::Black);

	// Start button rectangle
	this->m_StartButtonRect.setSize(sf::Vector2f(450, 100));
	// Exactly in middle of x axis
	position.x = (this->m_Window->getSize().x / 2) - (this->m_StartButtonRect.getLocalBounds().width / 2);
	// Variable on y axis by changing Y in Y.0f / 100.0f
	position.y = this->m_Window->getSize().y - (this->m_Window->getSize().y * (1 - (55.0f / 100.0f))) - (this->m_StartButtonRect.getLocalBounds().height / 2);
	this->m_StartButtonRect.setPosition(position);
	this->m_StartButtonRect.setFillColor(sf::Color(153, 217, 234, 255));

	// Start button text
	this->m_StartButtonText.setString("START");
	this->m_StartButtonText.setFont(this->m_SegoeUIFont);
	this->m_StartButtonText.setCharacterSize(40);
	position.x = (this->m_Window->getSize().x / 2) - (this->m_StartButtonText.getLocalBounds().width / 2);
	position.y = position.y + (this->m_StartButtonRect.getLocalBounds().height / 2) - (this->m_StartButtonText.getLocalBounds().height / 2);
	this->m_StartButtonText.setPosition(position);
	this->m_StartButtonText.setFillColor(sf::Color::Black);

	// Help button rectangle
	this->m_HelpButtonRect.setSize(sf::Vector2f(450, 100));
	// Exactly in middle of x axis
	position.x = (this->m_Window->getSize().x / 2) - (this->m_HelpButtonRect.getLocalBounds().width / 2);
	// Variable on y axis by changing Y in Y.0f / 100.0f
	position.y = this->m_Window->getSize().y - (this->m_Window->getSize().y * (1 - (80.0f / 100.0f))) - (this->m_HelpButtonRect.getLocalBounds().height / 2);
	this->m_HelpButtonRect.setPosition(position);
	this->m_HelpButtonRect.setFillColor(sf::Color(153, 217, 234, 255));


	// Help button text
	this->m_HelpButtonText.setString("How to play");
	this->m_HelpButtonText.setFont(this->m_SegoeUIFont);
	this->m_HelpButtonText.setCharacterSize(40);
	position.x = (this->m_Window->getSize().x / 2) - (this->m_HelpButtonText.getLocalBounds().width / 2);
	position.y = position.y + (this->m_HelpButtonRect.getLocalBounds().height / 2) - (this->m_HelpButtonText.getLocalBounds().height / 2);
	this->m_HelpButtonText.setPosition(position);
	this->m_HelpButtonText.setFillColor(sf::Color::Black);

}

void MainMenuState::HandleEvents()
{
	sf::Event event;
	while (this->m_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->m_Window->close();
		}
		// Start button
		if (event.type == sf::Event::MouseButtonReleased && MouseIntersect::Intersects(this->m_StartButtonRect.getPosition()
			, this->m_StartButtonRect.getSize(), sf::Mouse::getPosition(*this->m_Window)))
		{
			this->m_StartGame = true;
		}
		// Help button
		if (event.type == sf::Event::MouseButtonReleased && MouseIntersect::Intersects(this->m_HelpButtonRect.getPosition()
			, this->m_HelpButtonRect.getSize(), sf::Mouse::getPosition(*this->m_Window)))
		{
			this->m_GetHelp = true;
		}
	}
}

void MainMenuState::Update()
{
	if (this->m_Paused) return;
	// Reactive buttons
	// Start button
	if (MouseIntersect::Intersects(this->m_StartButtonRect.getPosition(),
		this->m_StartButtonRect.getSize(), sf::Mouse::getPosition(*this->m_Window)))
	{
		this->m_StartButtonRect.setFillColor(sf::Color(167, 228, 242, 255));
		this->m_StartButtonRect.setOutlineThickness(5.0f);
		this->m_StartButtonRect.setOutlineColor(sf::Color::Black);
	}
	else
	{
		this->m_StartButtonRect.setFillColor(sf::Color(153, 217, 234, 255));
		this->m_StartButtonRect.setOutlineThickness(0.0f);
	}
	// Help button
	if(MouseIntersect::Intersects(this->m_HelpButtonRect.getPosition(),
		this->m_HelpButtonRect.getSize(), sf::Mouse::getPosition(*this->m_Window)))
	{
		this->m_HelpButtonRect.setFillColor(sf::Color(167, 228, 242, 255));
		this->m_HelpButtonRect.setOutlineThickness(5.0f);
		this->m_HelpButtonRect.setOutlineColor(sf::Color::Black);
	}
	else
	{
		this->m_HelpButtonRect.setFillColor(sf::Color(153, 217, 234, 255));
		this->m_HelpButtonRect.setOutlineThickness(0.0f);
	}

	// Update state
	if (this->m_StartGame)
	{
		StateManager::AddState(std::make_unique<GameOngoingState>(this->m_Window));
		this->m_StartGame = false;
	}
	if (this->m_GetHelp)
	{
		std::cout << "Help kara\n";
		this->m_GetHelp = false;
	}
}

void MainMenuState::Draw()
{
	m_Window->clear(sf::Color::Cyan);
	m_Window->draw(this->m_HeadingText);
	m_Window->draw(this->m_StartButtonRect);
	m_Window->draw(this->m_StartButtonText);
	m_Window->draw(this->m_HelpButtonRect);
	m_Window->draw(this->m_HelpButtonText);
	m_Window->display();
}

void MainMenuState::Start()
{
	this->m_Paused = false;
}

void MainMenuState::Pause()
{
	this->m_Paused = true;
}
