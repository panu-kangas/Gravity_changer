#include "Player.hpp"


/*
	CONSTRUCTOR
*/

Player::Player()
{
	dirVec = {0, 0};
	moveSpeed = 130;
	coord = {100, 624}; // 640 (start of floor) - 16 (player size) = 624
	jumpPower = -3;

	isJumping = false;

	sprite.setSize({PLAYER_SIZE, PLAYER_SIZE});
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(coord);
}




/*
	MOVE
*/

void	Player::movePlayer(float dt, float gravity)
{
	coord.x += dirVec.x * moveSpeed * dt;

	if (isJumping)
	{
		coord.y += dirVec.y * moveSpeed * dt;
		dirVec.y += gravity;
	}
		

	if (coord.y > 624) // 624 = floor level for player
	{
		coord.y = 624;
		isJumping = false;
	}

	sprite.setPosition(coord);

}


/*
	SETTERS
*/

void	Player::setJumpState(bool state)
{
	isJumping = state;
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

