#ifndef GAMEHANDLER_HPP
# define GAMEHANDLER_HPP

#include "Player.hpp"

enum direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


class GameHandler
{
	private:

	Player	player;

	float	gravity;

	bool	upPressed;
	bool	downPressed;
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

	void	setKeypressState(bool state, int direction);


	Player	&getPlayer();

};


#endif