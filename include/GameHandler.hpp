#ifndef GAMEHANDLER_HPP
# define GAMEHANDLER_HPP

# include <iostream>

# include "Constants.hpp"
# include "Player.hpp"
# include "Map.hpp"



class GameHandler
{
	private:

	Player	player;
	Map		map;

	float	gravity;
	int		gravityDir;

	bool	upPressed;
//	bool	downPressed;
	bool	rightPressed;
	bool	leftPressed;
	bool	spacePressed;

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

	Player	&getPlayer();
	Map		&getMap();

};


#endif