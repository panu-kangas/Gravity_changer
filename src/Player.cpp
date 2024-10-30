#include "Player.hpp"
#include <math.h>



/*
	CONSTRUCTOR
*/

Player::Player()
{
	dirVec = {0, 0};
	moveSpeed = 130;
	coord = {100, 624}; // 640 (start of floor) - 16 (player size) = 624
	jumpPower = -3;

//	curTile.x = floor(coord.x) / TILE_SIZE;
//	curTile.y = floor(coord.y) / TILE_SIZE;
//	prevTile = curTile;

	isJumping = false;

	sprite.setSize({PLAYER_SIZE, PLAYER_SIZE});
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(coord);
}




/*
	MOVE
*/

void	Player::movePlayer(float dt, float gravity, int gravityDir)
{
	coord.x += dirVec.x * moveSpeed * dt;

	coord.y += dirVec.y * moveSpeed * dt;
	if (gravityDir == DOWN)
		dirVec.y += gravity * moveSpeed * dt;
	else if (gravityDir == UP)
		dirVec.y += gravity * moveSpeed * dt * -1;




/*
	if (coord.y > 624) // 624 = floor level for player
	{
		coord.y = 624;
		isJumping = false;
	}
*/

	sprite.setPosition(coord);

	// Update player tile coordinates
/*	sf::Vector2i tempTileCoord;

	tempTileCoord.x = floor(coord.x) / TILE_SIZE;
	tempTileCoord.y = floor(coord.y) / TILE_SIZE;

	if (tempTileCoord.x != curTile.x || tempTileCoord.y != curTile.y)
	{
		prevTile = curTile;
		curTile = tempTileCoord;
	}
*/

}


/*
	SETTERS
*/

void	Player::setJumpState(bool state, int gravityDir)
{

//	if (gravityDir == UP && state == true)
//		state = false;
//	else if (gravityDir == UP && state == false)
//		state = true;

	isJumping = state;

}

void	Player::fixPosAfterCollision(Map &map, bool *collFlags, int gravityDir)
{

	if (dirVec.x > 0 && collFlags[RIGHT] == true)
	{
		coord.x = floor(coord.x);
		coord.x -= (int)floor(coord.x) % PLAYER_SIZE;
	}

	if (dirVec.x < 0 && collFlags[LEFT] == true)
	{
		coord.x = floor(coord.x);
		coord.x += PLAYER_SIZE - ((int)floor(coord.x) % PLAYER_SIZE);
	}

	if (dirVec.y < 0 && collFlags[UP] == true)
	{
		coord.y = floor(coord.y);
		coord.y += PLAYER_SIZE - ((int)floor(coord.y) % PLAYER_SIZE);
		if (gravityDir == DOWN)
			dirVec.y = 0;
		else if (gravityDir == UP)
		{
			dirVec.y = -1;
			isJumping = false;
		}
	}

	if (dirVec.y > 0 && collFlags[DOWN] == true)
	{
		coord.y = floor(coord.y);
		coord.y -= (int)floor(coord.y) % PLAYER_SIZE;
		if (gravityDir == DOWN)
		{
			dirVec.y = 1;
			isJumping = false;
		}
		else if (gravityDir == UP)
			dirVec.y = 0;
	}

	for (int i = 0; i < 4; ++i)
		collFlags[i] = false;

	sprite.setPosition(coord);
}




/*
	GETTERS
*/

sf::RectangleShape	&Player::getSprite()
{
	return (sprite);
}

sf::Vector2f		&Player::getDirVec()
{
	return (dirVec);
}

sf::Vector2f		&Player::getCoord()
{
	return (coord);
}
/*
sf::Vector2i		Player::getCurTileCoord()
{
	return (curTile);
}

sf::Vector2i		Player::getPrevTileCoord()
{
	return (prevTile);
}
*/


	
float		&Player::getMoveSpeed()
{
	return (moveSpeed);
}

bool		&Player::getJumpState()
{
	return (isJumping);
}

float		&Player::getJumpPower()
{
	return (jumpPower);
}

