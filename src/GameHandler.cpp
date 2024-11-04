#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler()
{
	gravity = 0.05;
	gravityDir = DOWN;

	for (int i = 0; i < 8; ++i)
		pressedKeyArr[i] = false;

	for (int i = 0; i < 4; ++i)
		collFlags[i] = false;

	gameState = STARTSCREEN;

}



/*
	INITIALIZATION, is this needed...?
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

				if (gravityDir == UP || gravityDir == DOWN)
					player.getDirVec().y = player.getJumpPower();
				else if (gravityDir == LEFT || gravityDir == RIGHT)
					player.getDirVec().x = player.getJumpPower();

				if (gravityDir == UP && player.getDirVec().y < 0)
					player.getDirVec().y *= -1;
				else if (gravityDir == LEFT && player.getDirVec().x < 0)
					player.getDirVec().x *= -1;

			}
			setKeypressState(true, W); // is this needed?
			break ;

//		case sf::Keyboard::Scan::S :
//			tempVec.y = 1;
//			setKeypressState(true, DOWN);
//			break ;

		case sf::Keyboard::Scan::A :
			setKeypressState(true, A);
			break ;

		case sf::Keyboard::Scan::D :
			setKeypressState(true, D);
			break ;

		default:
			break ;
	}

	sf::Time gravityTime = gravityClock.getElapsedTime();

	if (gravityTime.asSeconds() < 3.0)
		return ;
	

	switch (event.key.code)
	{
		case sf::Keyboard::Up :
			if (pressedKeyArr[UPARR] == false && gravityDir != UP)
			{
				gravityDir = UP;
				setKeypressState(true, UPARR);
				player.setJumpState(true);
				gravityClock.restart();
			}
			break ;
		
		case sf::Keyboard::Down :
			if (pressedKeyArr[DOWNARR] == false && gravityDir != DOWN)
			{
				gravityDir = DOWN;
				setKeypressState(true, DOWNARR);
				player.setJumpState(true);
				gravityClock.restart();
			}
			break ;

		case sf::Keyboard::Left :
			if (pressedKeyArr[LEFTARR] == false && gravityDir != LEFT)
			{
				gravityDir = LEFT;
				setKeypressState(true, LEFTARR);
				player.setJumpState(true);
				gravityClock.restart();
			}
			break ;

		case sf::Keyboard::Right :
			if (pressedKeyArr[RIGHTARR] == false && gravityDir != RIGHT)
			{
				gravityDir = RIGHT;
				setKeypressState(true, RIGHTARR);
				player.setJumpState(true);
				gravityClock.restart();
			}
			break ;

		default :
			break ;
	}


}

void	GameHandler::checkRelease(sf::Event &event)
{
	switch (event.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			setKeypressState(false, W);
			break ;

//		case sf::Keyboard::Scan::S :
//			setKeypressState(false, DOWN);
//			break ;

		case sf::Keyboard::Scan::A :
			setKeypressState(false, A);
			break ;

		case sf::Keyboard::Scan::D :
			setKeypressState(false, D);
			break ;

		default:
			break ;
	}

	switch (event.key.code)
	{
		case sf::Keyboard::Up :
			setKeypressState(false, UPARR);
			break ;
		
		case sf::Keyboard::Down :
			setKeypressState(false, DOWNARR);
			break ;

		case sf::Keyboard::Left :
			setKeypressState(false, LEFTARR);
			break ;

		case sf::Keyboard::Right :
			setKeypressState(false, RIGHTARR);
			break ;

		default :
			break ;
	}
}


/*
	UPDATE
*/


void	GameHandler::updateGame(float dt)
{

	// MOVE THIS TO OWN FUNCTION

	static bool	hasMoved;

	if (pressedKeyArr[A])
	{
		if (gravityDir == UP || gravityDir == DOWN)
			player.getDirVec().x = -1;
		else if (gravityDir == RIGHT)
			player.getDirVec().y = 1;
		else if (gravityDir == LEFT)
			player.getDirVec().y = -1;
	}
	else if (pressedKeyArr[D])
	{
		if (gravityDir == UP || gravityDir == DOWN)
			player.getDirVec().x = 1;
		else if (gravityDir == RIGHT)
			player.getDirVec().y = -1;
		else if (gravityDir == LEFT)
			player.getDirVec().y = 1;
	}
	
	if (!pressedKeyArr[A] && !pressedKeyArr[D])
	{
		if (gravityDir == UP || gravityDir == DOWN)
			player.getDirVec().x = 0;
		else if (gravityDir == LEFT || gravityDir == RIGHT)
			player.getDirVec().y = 0;
	}

	// trying to fix "falls in the start" -bug
	// !!! ADD ARROW KEYS ALSO HERE !!!
	if (hasMoved == false && (pressedKeyArr[W] || pressedKeyArr[A] || pressedKeyArr[D]))
		hasMoved = true;

	//

	if (hasMoved == true)
	{
		player.movePlayer(dt, gravity, gravityDir);
		checkCollisions();
	}
	


}


// CREATE A COLLISION HANDLER CLASS...?
// Would be nice to get the collision handling code to somewhere else

void	GameHandler::checkCollisions()
{
	checkWallCollision();

	if (collFlags[UP] == true || collFlags[DOWN] == true || \
	collFlags[LEFT] == true || collFlags[RIGHT] == true)
		player.fixPosAfterCollision(map, collFlags, gravityDir);
	
	if (player.getSprite().getGlobalBounds().intersects(collectible.getSprite().getGlobalBounds()))
	{
		collectible.createNewCollectible(map);
		info.addScore(100);
	}


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

			if (gravityDir == UP || gravityDir == DOWN)
			{
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
			else
			{
				if (collisionTile.x < playerTile.x)
				{
					if (map.getTileType((playerCheckPoints[i].x + 10) / TILE_SIZE, playerCheckPoints[i].y / TILE_SIZE) == EMPTY)
						collFlags[LEFT] = true;
				}
				else if(collisionTile.x > playerTile.x)
				{
					if (map.getTileType((playerCheckPoints[i].x - 10) / TILE_SIZE, playerCheckPoints[i].y / TILE_SIZE) == EMPTY)
						collFlags[RIGHT] = true;
				}
				else if (collisionTile.y < playerTile.y)
					collFlags[UP] = true;
				else if (collisionTile.y > playerTile.y)
					collFlags[DOWN] = true;
			}
		}
	}

}



/*
	DRAW
*/

void	GameHandler::drawStartScreen(sf::RenderWindow &window, float dt)
{
	startscreen.drawScreen(window, dt);
}



void	GameHandler::drawGame(sf::RenderWindow &window)
{

	map.drawMap(window);

	window.draw(player.getSprite());

	collectible.drawCollectible(window);

	info.drawInfoScreen(window);

}


/*
	SETTERS
*/


void	GameHandler::setKeypressState(bool state, int key)
{
	pressedKeyArr[key] = state;
}

void	GameHandler::setGameState(int newState)
{
	gameState = newState;
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

Collectible &GameHandler::getCollectible()
{
	return (collectible);
}

int		GameHandler::getGameState()
{
	return (gameState);
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