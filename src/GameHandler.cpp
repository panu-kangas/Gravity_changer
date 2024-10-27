#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler()
{
	gravity = 10;

	upPressed = false;
	downPressed = false;
	rightPressed = false;
	leftPressed = false;
}



/*
	INITIALIZATION
*/

void	GameHandler::initGame()
{


}



/*
	CHECK INPUT
*/

void	GameHandler::checkInput(sf::Event &event)
{
	sf::Vector2f tempVec = {0, 0};

	switch (event.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			tempVec.y = -1;
			setKeypressState(true, UP);
			break ;

		case sf::Keyboard::Scan::S :
			tempVec.y = 1;
			setKeypressState(true, DOWN);
			break ;

		case sf::Keyboard::Scan::A :
			tempVec.x = -1;
			setKeypressState(true, LEFT);
			break ;

		case sf::Keyboard::Scan::D :
			tempVec.x = 1;
			setKeypressState(true, RIGHT);
			break ;

		default:
			return ;
	}

	player.getDirVec() = tempVec;
}

void	GameHandler::checkRelease(sf::Event &event)
{
	switch (event.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			setKeypressState(false, UP);
			break ;

		case sf::Keyboard::Scan::S :
			setKeypressState(false, DOWN);
			break ;

		case sf::Keyboard::Scan::A :
			setKeypressState(false, LEFT);
			break ;

		case sf::Keyboard::Scan::D :
			setKeypressState(false, RIGHT);
			break ;

		default:
			return ;
	}
}


/*
	UPDATE
*/


void	GameHandler::updateGame(float dt)
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		player.movePlayer(dt);

}


/*
	DRAW
*/


void	GameHandler::drawGame(sf::RenderWindow &window)
{
	window.draw(player.getSprite());

}


/*
	SETTERS
*/


void	GameHandler::setKeypressState(bool state, int direction)
{
	if (direction == UP)
		upPressed = state;
	else if (direction == DOWN)
		downPressed = state;
	else if (direction == LEFT)
		leftPressed = state;
	else if (direction == RIGHT)
		rightPressed = state;

}



/*
	GETTERS
*/


Player	&GameHandler::getPlayer()
{
	return (player);
}
