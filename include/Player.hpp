#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <SFML/Graphics.hpp>


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

	void	movePlayer(float dt);


	sf::RectangleShape	&getSprite();
	sf::Vector2f		&getDirVec();
	float				&getMoveSpeed();

};

#endif