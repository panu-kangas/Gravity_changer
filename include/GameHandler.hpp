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

	bool	upPressed;
//	bool	downPressed;
	bool	rightPressed;
	bool	leftPressed;


	public:

	GameHandler();
	~GameHandler() {};


	void	initGame();

	void	checkInput(sf::Event &event);
	void	checkRelease(sf::Event &event);

	void	updateGame(float dt);
	void	drawGame(sf::RenderWindow &window);

	bool	checkWallCollision(Player &player, Map &map);
	void	fixPlayerPos();



	void	setKeypressState(bool state, int direction);

	Player	&getPlayer();
	Map		&getMap();

};


#endif