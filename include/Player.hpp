#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <iostream>
# include "Constants.hpp"
# include "Map.hpp"

class Player
{
	private:

	sf::RectangleShape	m_sprite;
	sf::Vector2f		m_dirVec;
	sf::Vector2f		m_coord;

	float		m_moveSpeed;
	float		m_gravitySpeed;
	float		m_jumpPower;
	bool		m_isJumping;

//////

	public:

	Player();
	~Player() {};

	void	movePlayer(float dt, float gravity, int gravityDir);
	void	setJumpState(bool state, int keyPressed, bool gravityChange);
	void	fixPosAfterCollision(Map &map, bool *collFlags, int gravityDir);
	void	resetPlayer();

	// All getters return reference... is that bad...? 
	// Because now the values can be changed outside Player-class without a proper setter!
	sf::RectangleShape	&getSprite();
	sf::Vector2f		&getDirVec();
	sf::Vector2f		&getCoord();
	float				&getMoveSpeed();
	float				&getJumpPower();
	bool				&getJumpState();
};

#endif