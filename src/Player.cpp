#include "Player.hpp"


/*
	CONSTRUCTOR
*/

Player::Player()
{
	dirVec = {0, 0};
	moveSpeed = 100;
	coord = {100, 600};
	jumpPower = 50;

	isJumping = false;


	sprite.setSize({16, 16});
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(coord);
}




/*
	MOVE
*/

void	Player::movePlayer(float dt)
{
	coord.x += dirVec.x * moveSpeed * dt;
	coord.y += dirVec.y * moveSpeed * dt;
		

	if (coord.y > 600)
	{
		coord.y = 600;
		isJumping = false;
	}

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
	
float				&Player::getMoveSpeed()
{
	return (moveSpeed);
}