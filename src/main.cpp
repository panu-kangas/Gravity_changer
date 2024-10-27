#include <SFML/Graphics.hpp>

#include "GameHandler.hpp"

#define WINDOW_WIDTH 1056
#define WINDOW_HEIGHT 736



int main()
{
    auto window = sf::RenderWindow({WINDOW_WIDTH, WINDOW_HEIGHT}, "Platformer");
    window.setFramerateLimit(144);

	GameHandler game;

	sf::Clock	deltaClock;

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::KeyPressed)
				game.checkInput(event);
			else if (event.type == sf::Event::KeyReleased)
				game.checkRelease(event);

			if (event.type == sf::Event::KeyPressed 
			&& event.key.scancode == sf::Keyboard::Scan::Escape)
				window.close();
        }

		sf::Time dt = deltaClock.restart();

        window.clear();

		game.updateGame(dt.asSeconds());

		game.drawGame(window);

        window.display();
    }
}
