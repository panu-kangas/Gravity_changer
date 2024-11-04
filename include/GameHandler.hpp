#ifndef GAMEHANDLER_HPP
# define GAMEHANDLER_HPP

# include <iostream>

# include "Constants.hpp"
# include "Collectible.hpp"
# include "Player.hpp"
# include "Map.hpp"
# include "InfoScreen.hpp"
# include "StartScreen.hpp"


class GameHandler
{
	private:

	Player		player;
	Map			map;
	Collectible	collectible;
	InfoScreen	info;
	StartScreen	startscreen;

	sf::Clock	gravityClock;

	float	gravity;
	int		gravityDir;

	bool	pressedKeyArr[8];
	bool	collFlags[4];

	int		gameState;

	void	checkCollisions();
	void	checkWallCollision();
	void	getCollisionFlag(mapTile &tile);



	public:

	GameHandler();
	~GameHandler() {};


	void	initGame();

	void	checkInput(sf::Event &event);
	void	checkRelease(sf::Event &event);

	void	drawStartScreen(sf::RenderWindow &window, float dt);
	void	updateGame(float dt);
	void	drawGame(sf::RenderWindow &window);

	void	setKeypressState(bool state, int direction);
	void	setGameState(int newState);

	Player		&getPlayer();
	Map			&getMap();
	Collectible &getCollectible();
	int			getGameState();

};


#endif