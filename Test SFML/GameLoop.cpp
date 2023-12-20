#include "GameLoop.h"

GameLoop::GameLoop()
{


}

void GameLoop::Run()
{
	sf::RenderWindow window(sf::VideoMode(1050, 500), "Battleship");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	std::srand(345);

	sf::Vector2i MousePosition;

	Board PlayerBoard(0, 0, 500, User::Player);
	Board AIBoard(550, 0, 500, User::AI);

	// Game loop
	while (window.isOpen())
	{
		MousePosition = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Events
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color(53, 201, 242, 255));

		PlayerBoard.Draw(window, event, MousePosition, true);
		AIBoard.Draw(window, event, MousePosition, true);


		window.display();
	}
}
