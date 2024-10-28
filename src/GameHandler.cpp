#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler()
{
	gravity = 0.05;

	upPressed = false;
//	downPressed = false;
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
	switch (event.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			if (!player.getJumpState())
			{
				player.setJumpState(true);
				player.getDirVec().y = player.getJumpPower();
			}
			setKeypressState(true, UP); // is this needed?
			break ;

//		case sf::Keyboard::Scan::S :
//			tempVec.y = 1;
//			setKeypressState(true, DOWN);
//			break ;

		case sf::Keyboard::Scan::A :
			setKeypressState(true, LEFT);
			break ;

		case sf::Keyboard::Scan::D :
			setKeypressState(true, RIGHT);
			break ;

		default:
			return ;
	}

}

void	GameHandler::checkRelease(sf::Event &event)
{
	switch (event.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			setKeypressState(false, UP);
			break ;

//		case sf::Keyboard::Scan::S :
//			setKeypressState(false, DOWN);
//			break ;

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
	// MOVE THIS TO OWN FUNCTION

	if (leftPressed)
		player.getDirVec().x = -1;
	else if (rightPressed)
		player.getDirVec().x = 1;
	
	if (!leftPressed && !rightPressed)
		player.getDirVec().x = 0;

	//

	if (player.getJumpState() || leftPressed || rightPressed) // || downPressed
	{
		player.movePlayer(dt, gravity);
		if (checkWallCollision(player, map))
			fixPlayerPos();
	}


}

bool	GameHandler::checkWallCollision(Player &player, Map &map)
{
	sf::Vector2f	checkPoints[4];

	for (int i = 0; i < 4; ++i)
	{
		checkPoints[i].x = player.getCoord().x;
		checkPoints[i].y = player.getCoord().y;
	}

	checkPoints[1].x += PLAYER_SIZE;
	checkPoints[2].x += PLAYER_SIZE;
	checkPoints[2].y += PLAYER_SIZE;
	checkPoints[3].y += PLAYER_SIZE;

	for (int i = 0; i < 4; ++i)
	{
		if (map.getTileType(checkPoints[i].x / TILE_SIZE, checkPoints[i].x / TILE_SIZE) == WALL)
			return (true);
	}

	return (false);

}

void	GameHandler::fixPlayerPos()
{
	// Make temp dirVec, that goes to the opposite directions where player just moved
	// Remember gravity effect! It has already been reduced from dirvec.y!
	// make unit vector, and move pixel by pixel, until all the points are out of wall
}


/*
	DRAW
*/


void	GameHandler::drawGame(sf::RenderWindow &window)
{

	// MAP

	map.drawMap(window);

	// PLAYER
	window.draw(player.getSprite());

}


/*
	SETTERS
*/


void	GameHandler::setKeypressState(bool state, int direction)
{
	if (direction == UP)
		upPressed = state;
	else if (direction == LEFT)
		leftPressed = state;
	else if (direction == RIGHT)
		rightPressed = state;

	/*
	else if (direction == DOWN)
		downPressed = state;
	*/

}



/*
	GETTERS
*/


Player	&GameHandler::getPlayer()
{
	return (player);
}

Map		&GameHandler::getMap()
{
	return (map);
}

