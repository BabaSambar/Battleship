#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameLoop.h"

// Change "main" -> "WinMain" while release mode
int main() {
	GameLoop game;
	game.Run();
	return 0;
}