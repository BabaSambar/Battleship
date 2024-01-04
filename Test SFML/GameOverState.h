#pragma once
#include "GameState.h"
class GameOverState : public GameState
{
public:
	GameOverState(sf::RenderWindow* window);

	void HandleEvents();
	void Update();
	void Draw();

	void Start();
	void Pause();
private:
	bool m_Paused;
	sf::RenderWindow* m_Window;
	sf::RectangleShape rect;
};

