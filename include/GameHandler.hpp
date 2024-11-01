#ifndef GAMEHANDLER_HPP
# define GAMEHANDLER_HPP

# include <iostream>

# include "Constants.hpp"
# include "Collectible.hpp"
# include "Player.hpp"
# include "Map.hpp"



class GameHandler
{
	private:

	Player		player;
	Map			map;
	Collectible	collectible;

	sf::Clock	gravityClock;

	float	gravity;
	int		gravityDir;

	bool	pressedKeyArr[8];
	bool	collFlags[4];

	void	checkCollisions();
	void	checkWallCollision();
	void	getCollisionFlag(mapTile &tile);



	public:

	GameHandler();
	~GameHandler() {};


	void	initGame();

	void	checkInput(sf::Event &event);
	void	checkRelease(sf::Event &event);

	void	updateGame(float dt);
	void	drawGame(sf::RenderWindow &window);




	void	setKeypressState(bool state, int direction);

	Player		&getPlayer();
	Map			&getMap();
	Collectible &getCollectible();

};


#endif