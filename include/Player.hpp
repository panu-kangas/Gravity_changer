#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <SFML/Graphics.hpp>
# include <iostream>

# include "Constants.hpp"


class Player
{
	private:

	sf::RectangleShape	sprite;
	sf::Vector2f		dirVec;
	sf::Vector2f		coord;

	float		moveSpeed;
	float		jumpPower;

	bool		isJumping;


	public:

	Player();
	~Player() {};

	void	movePlayer(float dt, float gravity);

	void	setJumpState(bool state);

	sf::RectangleShape	&getSprite();
	sf::Vector2f		&getDirVec();
	sf::Vector2f		&getCoord();
	float				&getMoveSpeed();
	float				&getJumpPower();
	bool				&getJumpState();


};

#endif