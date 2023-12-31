#pragma once
#include "GameState.h"
#include "GameOngoingState.h"

#include "StateManager.h"
#include "MouseIntersect.h"
#include "FontManager.h"

class MainMenuState : public GameState
{
public:
	MainMenuState(sf::RenderWindow* window);

	void HandleEvents();
	void Update();
	void Draw();

	void Start();
	void Pause();

private:
	bool m_Paused;

	// Font for all texts
	sf::Font m_SegoeUIFont;

	sf::RenderWindow* m_Window;
	// Heading text
	sf::Text m_HeadingText;
	// Start button rectangle
	sf::RectangleShape m_StartButtonRect;
	// Start button text
	sf::Text m_StartButtonText;
	// Help button rectangle
	sf::RectangleShape m_HelpButtonRect;
	// Help button text
	sf::Text m_HelpButtonText;
	bool m_StartGame;
	bool m_GetHelp;
};

