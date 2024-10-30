#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler()
{
	gravity = 0.05;
	gravityDir = DOWN;

	upPressed = false;
//	downPressed = false;
	rightPressed = false;
	leftPressed = false;
	spacePressed = false;

	for (int i = 0; i < 4; ++i)
		collFlags[i] = false;

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
				player.setJumpState(true, gravityDir);
				player.getDirVec().y = player.getJumpPower();
				if (gravityDir == UP && player.getDirVec().y < 0)
					player.getDirVec().y *= -1;
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
		
		case sf::Keyboard::Scan::Space :
			if (spacePressed == false && gravityDir == DOWN)
				gravityDir = UP;
			else if (spacePressed == false && gravityDir == UP)
				gravityDir = DOWN;
			spacePressed = true;
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

		case sf::Keyboard::Scan::Space :
			spacePressed = false;
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

	player.movePlayer(dt, gravity, gravityDir);
	checkCollisions();
	


}

void	GameHandler::checkCollisions()
{
	checkWallCollision();

	if (collFlags[UP] == true || collFlags[DOWN] == true || \
	collFlags[LEFT] == true || collFlags[RIGHT] == true)
		player.fixPosAfterCollision(map, collFlags, gravityDir);


}

void	GameHandler::checkWallCollision()
{
	sf::Vector2i	playerTileCoord;

	playerTileCoord.x = floor(player.getCoord().x) / TILE_SIZE;
	playerTileCoord.y = floor(player.getCoord().y) / TILE_SIZE;


	for (int y = playerTileCoord.y - 1; y < playerTileCoord.y + 2; ++y)
	{
		if (y < 0 || y >= (WINDOW_HEIGHT / TILE_SIZE))
			continue ;
			
		for (int x = playerTileCoord.x - 1; x < playerTileCoord.x + 2; ++x)
		{
			if (x < 0 || x >= (WINDOW_WIDTH / TILE_SIZE))
				continue ;
			
			mapTile &tile = map.getTileVec()[y][x];
			if (tile.type == EMPTY)
				continue ;

			if (tile.shape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
				getCollisionFlag(tile);
		}
	}

}


void	GameHandler::getCollisionFlag(mapTile &tile)
{
	sf::Vector2f	playerCheckPoints[4];
	sf::FloatRect	playerBounds = player.getSprite().getGlobalBounds();
	sf::FloatRect	tileBounds = tile.shape.getGlobalBounds();

	playerCheckPoints[0].x = playerBounds.left;
	playerCheckPoints[0].y = playerBounds.top;
	playerCheckPoints[1].x = playerBounds.left + PLAYER_SIZE;
	playerCheckPoints[1].y = playerBounds.top;
	playerCheckPoints[2].x = playerBounds.left + PLAYER_SIZE;
	playerCheckPoints[2].y = playerBounds.top + PLAYER_SIZE;
	playerCheckPoints[3].x = playerBounds.left;
	playerCheckPoints[3].y = playerBounds.top + PLAYER_SIZE;

	int i;
	for (i = 0; i < 4; ++i)
	{
		if (tileBounds.contains(playerCheckPoints[i]))
		{
			sf::Vector2i	collisionTile;
			collisionTile.x = floor(playerCheckPoints[i].x) / TILE_SIZE;
			collisionTile.y = floor(playerCheckPoints[i].y) / TILE_SIZE;

			sf::Vector2i	playerTile;
			playerTile.x = floor(playerBounds.left + PLAYER_SIZE / 2) / TILE_SIZE;
			playerTile.y = floor(playerBounds.top + PLAYER_SIZE / 2) / TILE_SIZE;


			// SMALL BUG HERE! Player can cut through the corners of walls

			// Example: Player jumps up and hugs towards a wall on the right side
			// When most of the rect has gone by the upper level of the hugged wall, only
			// downright point (index 2) of player is left colliding.
			// This triggers second if, because playerTile is based on centre of player
			// (so collision tile is one down from player --> bigger)
			// WHAT SHOULD BE TRIGGERED IS collRight CONDITION
			
			// How to fix this?

			if (collisionTile.y < playerTile.y)
			{
				if (map.getTileType(playerCheckPoints[i].x / TILE_SIZE, (playerCheckPoints[i].y + 10) / TILE_SIZE) == EMPTY)
					collFlags[UP] = true;
			}
			else if (collisionTile.y > playerTile.y)
			{
				if (map.getTileType(playerCheckPoints[i].x / TILE_SIZE, (playerCheckPoints[i].y - 10) / TILE_SIZE) == EMPTY)
					collFlags[DOWN] = true;
			}
			else if (collisionTile.x < playerTile.x)
				collFlags[LEFT] = true;
			else if(collisionTile.x > playerTile.x)
				collFlags[RIGHT] = true;
		}
	}

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



/*
	OLD VERSION:


bool	GameHandler::checkWallCollision(Player &player, Map &map, float dt)
{
	sf::Vector2f	checkPoints[4];

	for (int i = 0; i < 4; ++i)
	{
		checkPoints[i].x = player.getCoord().x + (player.getDirVec().x * player.getMoveSpeed() * dt);

		if (player.getJumpState())
			checkPoints[i].y = player.getCoord().y + (player.getDirVec().y * player.getMoveSpeed() * dt);
		else
			checkPoints[i].y = player.getCoord().y;
	}

	checkPoints[1].x += PLAYER_SIZE;
	checkPoints[2].x += PLAYER_SIZE;
	checkPoints[2].y += PLAYER_SIZE;
	checkPoints[3].y += PLAYER_SIZE;

	sf::Vector2f	collisionTile = {-100, -100};
	sf::Vector2f	checkTile;

	for (int i = 0; i < 4; ++i)
	{
		checkTile = {checkPoints[i].x / TILE_SIZE, checkPoints[i].y / TILE_SIZE};

		if (map.getTileType(checkTile.x, checkTile.y) == WALL)
			collisionTile = checkTile;
	}

	return (false);

}






*/