#include "Player.hpp"
#include <math.h>

/*
	CONSTRUCTOR
*/

Player::Player()
{
	m_dirVec = {0, 0};
	m_moveSpeed = 170;
	m_gravitySpeed = 140;
	m_coord = {100, 624}; // 640 (start of floor) - 16 (player size) = 624
	m_jumpPower = -3;

	m_isJumping = false;

	m_sprite.setSize({PLAYER_SIZE, PLAYER_SIZE});
	m_sprite.setFillColor(sf::Color::Green);
	m_sprite.setPosition(m_coord);
}

/*
	MOVE
*/

void	Player::movePlayer(float dt, float gravity, int gravityDir)
{
	if (m_dirVec.x > PLAYER_MAX_SPEED)
		m_dirVec.x = PLAYER_MAX_SPEED;
	else if (m_dirVec.x < -PLAYER_MAX_SPEED)
		m_dirVec.x = -PLAYER_MAX_SPEED;
	if (m_dirVec.y > PLAYER_MAX_SPEED)
		m_dirVec.y = PLAYER_MAX_SPEED;
	else if (m_dirVec.y < -PLAYER_MAX_SPEED)
		m_dirVec.y = -PLAYER_MAX_SPEED;

	m_coord.x += m_dirVec.x * (m_moveSpeed) * dt;
	m_coord.y += m_dirVec.y * (m_moveSpeed) * dt;

	if (gravityDir == DOWN)
		m_dirVec.y += gravity * (m_gravitySpeed) * dt;
	else if (gravityDir == UP)
		m_dirVec.y += gravity * (m_gravitySpeed) * dt * -1;
	else if (gravityDir == LEFT)
		m_dirVec.x += gravity * (m_gravitySpeed) * dt * -1;
	else if (gravityDir == RIGHT)
		m_dirVec.x += gravity * (m_gravitySpeed) * dt;

	m_sprite.setPosition(m_coord);
}

/*
	RESET
*/

void	Player::resetPlayer()
{
	m_coord = {100, 624};
	m_dirVec = {0, 0};
	m_isJumping = false;
}

/*
	SETTERS
*/

void	Player::setJumpState(bool state, int keyPressed, bool gravityChange)
{
	m_isJumping = state;

	if (state == true && gravityChange == false)
	{
		if (keyPressed == W)
			m_dirVec.y = m_jumpPower;
		else if (keyPressed == S)
			m_dirVec.y = m_jumpPower * -1;
		else if (keyPressed == A)
			m_dirVec.x = m_jumpPower;
		else if (keyPressed == D)
			m_dirVec.x = m_jumpPower * -1;
	}
}

void	Player::fixPosAfterCollision(Map &map, bool *collFlags, int gravityDir)
{
	// If moving right and collision to right, fix player next to wall and adjust m_dirVec.
	if (m_dirVec.x > 0 && collFlags[RIGHT] == true)
	{
		m_coord.x = floor(m_coord.x);
		m_coord.x -= (int)floor(m_coord.x) % PLAYER_SIZE;
		if (gravityDir == LEFT)
			m_dirVec.x = 0;
		else if (gravityDir == RIGHT)
		{
			m_dirVec.x = 1; // small gravitational pull to keep player on ground
			m_isJumping = false;
		}
	}

	if (m_dirVec.x < 0 && collFlags[LEFT] == true)
	{
		m_coord.x = floor(m_coord.x);
		m_coord.x += PLAYER_SIZE - ((int)floor(m_coord.x) % PLAYER_SIZE);
		if (gravityDir == RIGHT)
			m_dirVec.x = 0;
		else if (gravityDir == LEFT)
		{
			m_dirVec.x = -1;
			m_isJumping = false;
		}
	}

	if (m_dirVec.y < 0 && collFlags[UP] == true)
	{
		m_coord.y = floor(m_coord.y);
		m_coord.y += PLAYER_SIZE - ((int)floor(m_coord.y) % PLAYER_SIZE);
		if (gravityDir == DOWN)
			m_dirVec.y = 0;
		else if (gravityDir == UP)
		{
			m_dirVec.y = -1;
			m_isJumping = false;
		}
	}

	if (m_dirVec.y > 0 && collFlags[DOWN] == true)
	{
		m_coord.y = floor(m_coord.y);
		m_coord.y -= (int)floor(m_coord.y) % PLAYER_SIZE;
		if (gravityDir == DOWN)
		{
			m_dirVec.y = 1;
			m_isJumping = false;
		}
		else if (gravityDir == UP)
			m_dirVec.y = 0;
	}

	for (int i = 0; i < 4; ++i)
		collFlags[i] = false;

	m_sprite.setPosition(m_coord);
}

/*
	GETTERS
*/

sf::RectangleShape	&Player::getSprite()
{
	return (m_sprite);
}

sf::Vector2f		&Player::getDirVec()
{
	return (m_dirVec);
}

sf::Vector2f		&Player::getCoord()
{
	return (m_coord);
}
	
float		&Player::getMoveSpeed()
{
	return (m_moveSpeed);
}

bool		&Player::getJumpState()
{
	return (m_isJumping);
}

float		&Player::getJumpPower()
{
	return (m_jumpPower);
}

