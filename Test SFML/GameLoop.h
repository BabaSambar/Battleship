#pragma once
#include <iostream>

#include "StateManager.h"
#include "MainMenuState.h"
#include "GameOngoingState.h"
#include "GameOverState.h"

class GameLoop
{
public:
	// Constructor to initialize textures, sounds and fonts
	GameLoop();
	void Run();

private:
	sf::RenderWindow m_Window;
};

