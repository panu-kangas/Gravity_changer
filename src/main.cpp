#include <SFML/Graphics.hpp>
#include "GameHandler.hpp"

void	fixGameWindow(sf::RenderWindow &window);


int main()
{
    auto window = sf::RenderWindow({GAME_WIDTH, GAME_HEIGHT}, "Platformer");
    window.setFramerateLimit(144);
	fixGameWindow(window);

	GameHandler game;
	game.getMap().initMap();

	sf::Clock	deltaClock;

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

			if ((game.getGameState() == STARTSCREEN || game.getGameState() == END) 
			&& event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
			{
				game.setGameState(GAME);
				game.initGame();
			}
			else if (event.type == sf::Event::KeyPressed)
				game.checkInput(event);
			else if (event.type == sf::Event::KeyReleased)
				game.checkRelease(event);
        }

		sf::Time dt = deltaClock.restart();

        window.clear();

		if (game.getGameState() == STARTSCREEN)
			game.drawStartScreen(window, dt.asSeconds());
		else if (game.getGameState() == END)
			game.drawEndScreen(window);
		else
		{
			game.updateGame(dt.asSeconds());
			game.drawGame(window);
		}

        window.display();
    }
}


/*
	HELPER FUNCTION
*/

void	fixGameWindow(sf::RenderWindow &window)
{
	sf::Vector2i monitorSize;
	monitorSize.x = sf::VideoMode::getDesktopMode().width;
	monitorSize.y = sf::VideoMode::getDesktopMode().height;

	// Fix game window size to be 70% of monitor
	sf::Vector2u gameWindowSize;
	gameWindowSize.x = monitorSize.x * 0.7;
	gameWindowSize.y = monitorSize.y * 0.7;
	window.setSize(gameWindowSize);

	// Center window
	sf::Vector2i	intGameWindowSize;
	intGameWindowSize.x = gameWindowSize.x;
	intGameWindowSize.y = gameWindowSize.y;
	window.setPosition({monitorSize.x / 2 - intGameWindowSize.x / 2, monitorSize.y / 2 - intGameWindowSize.y / 2});
}

