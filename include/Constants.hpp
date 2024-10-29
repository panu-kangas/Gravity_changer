#ifndef CONSTANTS_HPP
# define CONSTANTS_HPP

# define WINDOW_WIDTH 1056
# define WINDOW_HEIGHT 736

# define TILE_SIZE 32
# define PLAYER_SIZE 16

# include <SFML/Graphics.hpp> // this is not a good place for this...!


enum direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum tiletype
{
	EMPTY,
	WALL
};

struct mapTile
{
	int	type;
	sf::RectangleShape	shape;

	// something else...?
};


#endif