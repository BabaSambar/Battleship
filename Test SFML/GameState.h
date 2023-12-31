#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class GameState
{
public:
	GameState() {}
	// Handle events
	virtual void HandleEvents() = 0;
	// Update state members
	virtual void Update() = 0;
	// Draw state members on window
	virtual void Draw() = 0;

	// Pause state
	virtual void Pause() {}
	// Start state
	virtual void Start() {}
};
