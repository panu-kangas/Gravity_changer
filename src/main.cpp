#include <SFML/Graphics.hpp>
#include "GameHandler.hpp"


int main()
{
    auto window = sf::RenderWindow({WINDOW_WIDTH, WINDOW_HEIGHT}, "Platformer");
    window.setFramerateLimit(144);

	GameHandler game;

	game.getMap().initMap();
	game.getCollectible().createNewCollectible(game.getMap());
	

	sf::Clock	deltaClock;

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (game.getGameState() == STARTSCREEN && event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
					game.setGameState(GAME);
			}
			else if (event.type == sf::Event::KeyPressed)
				game.checkInput(event);
			else if (event.type == sf::Event::KeyReleased)
				game.checkRelease(event);

			if (event.type == sf::Event::KeyPressed 
			&& event.key.scancode == sf::Keyboard::Scan::Escape)
				window.close();
        }

		sf::Time dt = deltaClock.restart();

        window.clear();

		if (game.getGameState() == STARTSCREEN)
			game.drawStartScreen(window, dt.asSeconds());
		else
		{
			game.updateGame(dt.asSeconds());
			game.drawGame(window);
		}

        window.display();
    }
}
