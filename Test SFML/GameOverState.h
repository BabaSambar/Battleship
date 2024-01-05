#pragma once
#include "GameState.h"
#include "FontManager.h"
#include "StateManager.h"
#include "TurnManager.h"

class GameOverState : public GameState
{
public:
	GameOverState(sf::RenderWindow* window, User Winner);

	void HandleEvents();
	void Update();
	void Draw();

	void Start();
	void Pause();
private:
	bool m_Paused;
	bool m_Restart;
	sf::Font m_SegoeUIFont;

	sf::RenderWindow* m_Window;
	// Play again button
	sf::RectangleShape m_RestartRect;
	sf::Text m_RestartText;
	// Game over text
	sf::Text m_GameOverText;
};

