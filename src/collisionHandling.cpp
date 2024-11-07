#include "GameHandler.hpp"
#include <math.h>

void	GameHandler::checkCollisions()
{
	checkWallCollision();

	if (m_collisionFlagArr[UP] || m_collisionFlagArr[DOWN] || \
	m_collisionFlagArr[LEFT] || m_collisionFlagArr[RIGHT])
		m_player.fixPosAfterCollision(m_map, m_collisionFlagArr, m_gravityDir);
	
	if (m_player.getSprite().getGlobalBounds().intersects(m_collectible.getSprite().getGlobalBounds()))
	{
		m_collectible.createNewCollectible(m_map, m_player);
		m_info.addScore(100);
	}
}

void	GameHandler::checkWallCollision()
{
	sf::Vector2i	playerTileCoord;

	playerTileCoord.x = floor(m_player.getCoord().x) / TILE_SIZE;
	playerTileCoord.y = floor(m_player.getCoord().y) / TILE_SIZE;

	for (int y = playerTileCoord.y - 1; y < playerTileCoord.y + 2; ++y)
	{
		if (y < 0 || y >= (GAME_HEIGHT / TILE_SIZE))
			continue ;
			
		for (int x = playerTileCoord.x - 1; x < playerTileCoord.x + 2; ++x)
		{
			if (x < 0 || x >= (GAME_WIDTH / TILE_SIZE))
				continue ;
			
			mapTile &tile = m_map.getTileVec()[y][x];
			if (tile.type == EMPTY)
				continue ;

			if (tile.shape.getGlobalBounds().intersects(m_player.getSprite().getGlobalBounds()))
				getCollisionFlag(tile);
		}
	}
}
// SMALL BUG HERE! Player can slightly cut through the corners of walls.
// Check explanation below the function implementation.

void	GameHandler::getCollisionFlag(mapTile &tile)
{
	sf::Vector2f	checkPoint[4]; // player's corner points in pixels
	sf::FloatRect	playerBounds = m_player.getSprite().getGlobalBounds();
	sf::FloatRect	tileBounds = tile.shape.getGlobalBounds();

	checkPoint[0].x = playerBounds.left;
	checkPoint[0].y = playerBounds.top;
	checkPoint[1].x = playerBounds.left + PLAYER_SIZE;
	checkPoint[1].y = playerBounds.top;
	checkPoint[2].x = playerBounds.left + PLAYER_SIZE;
	checkPoint[2].y = playerBounds.top + PLAYER_SIZE;
	checkPoint[3].x = playerBounds.left;
	checkPoint[3].y = playerBounds.top + PLAYER_SIZE;

	for (int i = 0; i < 4; ++i)
	{
		if (tileBounds.contains(checkPoint[i]))
		{
			// The tile on map that collision happened with
			sf::Vector2i	collisionTile;
			collisionTile.x = floor(checkPoint[i].x) / TILE_SIZE;
			collisionTile.y = floor(checkPoint[i].y) / TILE_SIZE;

			// The tile player is on (based on player's mid point)
			sf::Vector2i	playerTile;
			playerTile.x = floor(playerBounds.left + PLAYER_SIZE / 2) / TILE_SIZE;
			playerTile.y = floor(playerBounds.top + PLAYER_SIZE / 2) / TILE_SIZE;

			// Check to see that on which side of the player the collisionTile is located. 
			if (m_gravityDir == UP || m_gravityDir == DOWN)
			{
				if (collisionTile.y < playerTile.y)
				{
					// Check to see if the tile above collision point is empty
					if (m_map.getTileType(checkPoint[i].x / TILE_SIZE, (checkPoint[i].y + 30) / TILE_SIZE) == EMPTY)
						m_collisionFlagArr[UP] = true;
				}
				else if (collisionTile.y > playerTile.y)
				{
					if (m_map.getTileType(checkPoint[i].x / TILE_SIZE, (checkPoint[i].y - 30) / TILE_SIZE) == EMPTY)
						m_collisionFlagArr[DOWN] = true;
				}
				else if (collisionTile.x < playerTile.x)
					m_collisionFlagArr[LEFT] = true;
				else if(collisionTile.x > playerTile.x)
					m_collisionFlagArr[RIGHT] = true;
			}
			else
			{
				if (collisionTile.x < playerTile.x)
				{
					if (m_map.getTileType((checkPoint[i].x + 30) / TILE_SIZE, checkPoint[i].y / TILE_SIZE) == EMPTY)
						m_collisionFlagArr[LEFT] = true;
				}
				else if(collisionTile.x > playerTile.x)
				{
					if (m_map.getTileType((checkPoint[i].x - 30) / TILE_SIZE, checkPoint[i].y / TILE_SIZE) == EMPTY)
						m_collisionFlagArr[RIGHT] = true;
				}
				else if (collisionTile.y < playerTile.y)
					m_collisionFlagArr[UP] = true;
				else if (collisionTile.y > playerTile.y)
					m_collisionFlagArr[DOWN] = true;
			}
		}
	}
}

	// SMALL BUG explanation:

	// Example: Player jumps up and hugs towards a wall on the right side
	// When most of the rect has gone by the upper level of the hugged wall, only
	// downright point (index 2) of player is left colliding.
	// This triggers the wrong if-statement, because playerTile is based on centre of player
	// (so collision tile is one down from player --> bigger)
	// WHAT SHOULD BE TRIGGERED IS collRight CONDITION
	// How to fix this?
	// Maybe use player dirVec to "draw a line" and check the intersection coord.
	// That could tell us that on which side the collision happened