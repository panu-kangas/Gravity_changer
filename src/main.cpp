#include <SFML/Graphics.hpp>
#include "GameHandler.hpp"


int main()
{

	sf::Vector2i monitorSize;

	monitorSize.x = sf::VideoMode::getDesktopMode().width;
	monitorSize.y = sf::VideoMode::getDesktopMode().height;

    auto window = sf::RenderWindow({GAME_WIDTH, GAME_HEIGHT}, "Platformer");
    window.setFramerateLimit(144);

	// Fix game window size
	sf::Vector2u gameWindowSize;
	gameWindowSize.x = monitorSize.x * 0.7;
	gameWindowSize.y = monitorSize.y * 0.7;

	window.setSize(gameWindowSize);

	// Center window
	sf::Vector2i	intGameWindowSize;
	intGameWindowSize.x = gameWindowSize.x;
	intGameWindowSize.y = gameWindowSize.y;

	window.setPosition({intGameWindowSize.x / 2 - GAME_WIDTH / 2, intGameWindowSize.y / 2 - GAME_HEIGHT / 2});


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
