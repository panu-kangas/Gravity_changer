#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <iostream>

# include "Constants.hpp"
# include "Map.hpp"



class Player
{
	private:

	sf::RectangleShape	sprite;
	sf::Vector2f		dirVec;
	sf::Vector2f		coord;

	float		moveSpeed;
	float		jumpPower;

//	sf::Vector2i	curTile;
//	sf::Vector2i	prevTile;

	bool		isJumping;


	public:

	Player();
	~Player() {};

	void	movePlayer(float dt, float gravity, int gravityDir);

	void	setJumpState(bool state);
	void	fixPosAfterCollision(Map &map, bool *collFlags, int gravityDir);

	void	resetPlayer();


	// These should probably not all return reference, since then they can be changed without setter!
	sf::RectangleShape	&getSprite();
	sf::Vector2f		&getDirVec();
	sf::Vector2f		&getCoord();
	float				&getMoveSpeed();
	float				&getJumpPower();
	bool				&getJumpState();


};

#endif