#include "GameHandler.hpp"
#include <math.h>

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler()
{
	gravity = 0.05;
	gravityDir = DOWN;
	firstGravityChange = false;

	for (int i = 0; i < 8; ++i)
		pressedKeyArr[i] = false;

	for (int i = 0; i < 4; ++i)
		collFlags[i] = false;

	gameState = STARTSCREEN;

}



/*
	INITIALIZATION
*/

void	GameHandler::initGame()
{
	collectible.createNewCollectible(map, player);
	player.resetPlayer();
	info.resetInfo();
	end.getScoreString() = "";
	gravityDir = DOWN;
	firstGravityChange = false;
}



/*
	CHECK INPUT
*/

void	GameHandler::checkInput(sf::Event &event)
{
	// MOVEMENT
	switch (event.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			if (gravityDir == DOWN && !player.getJumpState())
			{
				player.setJumpState(true);
				player.getDirVec().y = player.getJumpPower();
			}
			setKeypressState(true, W);
			break ;

		case sf::Keyboard::Scan::S :
			if (gravityDir == UP && !player.getJumpState())
			{
				player.setJumpState(true);
				player.getDirVec().y = player.getJumpPower() * -1;
			}
			setKeypressState(true, S);
			break ;

		case sf::Keyboard::Scan::A :
			if (gravityDir == RIGHT && !player.getJumpState())
			{
				player.setJumpState(true);
				player.getDirVec().x = player.getJumpPower();
			}
			setKeypressState(true, A);
			break ;

		case sf::Keyboard::Scan::D :
			if (gravityDir == LEFT && !player.getJumpState())
			{
				player.setJumpState(true);
				player.getDirVec().x = player.getJumpPower() * -1;
			}
			setKeypressState(true, D);
			break ;

		default:
			break ;
	}

	// GRAVITY

	if (firstGravityChange && gravityClock.getElapsedTime().asSeconds() < 2.5)
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

	if (!firstGravityChange && \
	(pressedKeyArr[UPARR] || pressedKeyArr[DOWNARR] || pressedKeyArr[LEFTARR] || pressedKeyArr[RIGHTARR]))
		firstGravityChange = true;

}

void	GameHandler::checkRelease(sf::Event &event)
{
	switch (event.key.scancode)
	{
		case sf::Keyboard::Scan::W :
			setKeypressState(false, W);
			break ;

		case sf::Keyboard::Scan::S :
			setKeypressState(false, S);
			break ;

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

	if (info.getCurGameTime() <= 0)
	{
		gameState = END;
		return ;
	}

	// MOVE THIS TO OWN FUNCTION

	static bool	hasMoved;

	if (gravityDir == DOWN || gravityDir == UP)
	{
		if (pressedKeyArr[A])
			player.getDirVec().x = -1;
		else if (pressedKeyArr[D])
			player.getDirVec().x = 1;
		else if (!pressedKeyArr[A] && !pressedKeyArr[D])
			player.getDirVec().x = 0;
	}
	else
	{
		if (pressedKeyArr[W])
			player.getDirVec().y = -1;
		else if (pressedKeyArr[S])
			player.getDirVec().y = 1;
		else if (!pressedKeyArr[W] && !pressedKeyArr[S])
			player.getDirVec().y = 0;
	}

	// trying to fix "falls in the start" -bug
	if (hasMoved == false && (pressedKeyArr[W] || pressedKeyArr[A] || pressedKeyArr[D] || pressedKeyArr[S] \
	|| pressedKeyArr[UPARR] || pressedKeyArr[LEFTARR] || pressedKeyArr[RIGHTARR] || pressedKeyArr[DOWNARR]))
		hasMoved = true;

	//

	if (hasMoved == true)
	{
		player.movePlayer(dt, gravity, gravityDir);
		checkCollisions();
	}

	if (!firstGravityChange)
		info.update(2.5);
	else
		info.update(gravityClock.getElapsedTime().asSeconds());


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
		collectible.createNewCollectible(map, player);
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
		if (y < 0 || y >= (GAME_HEIGHT / TILE_SIZE))
			continue ;
			
		for (int x = playerTileCoord.x - 1; x < playerTileCoord.x + 2; ++x)
		{
			if (x < 0 || x >= (GAME_WIDTH / TILE_SIZE))
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
					if (map.getTileType(playerCheckPoints[i].x / TILE_SIZE, (playerCheckPoints[i].y + 30) / TILE_SIZE) == EMPTY)
						collFlags[UP] = true;
				}
				else if (collisionTile.y > playerTile.y)
				{
					if (map.getTileType(playerCheckPoints[i].x / TILE_SIZE, (playerCheckPoints[i].y - 30) / TILE_SIZE) == EMPTY)
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
					if (map.getTileType((playerCheckPoints[i].x + 30) / TILE_SIZE, playerCheckPoints[i].y / TILE_SIZE) == EMPTY)
						collFlags[LEFT] = true;
				}
				else if(collisionTile.x > playerTile.x)
				{
					if (map.getTileType((playerCheckPoints[i].x - 30) / TILE_SIZE, playerCheckPoints[i].y / TILE_SIZE) == EMPTY)
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

void	GameHandler::drawEndScreen(sf::RenderWindow &window)
{
	if (end.getScoreString().empty())
		end.setScoreString(info.getScore());

	end.draw(window);
}




void	GameHandler::drawGame(sf::RenderWindow &window)
{
	if (gameState == END)
		return ;

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

InfoScreen	&GameHandler::getInfoScreen()
{
	return (info);
}


int		GameHandler::getGameState()
{
	return (gameState);
}


