#ifndef CONSTANTS_HPP
# define CONSTANTS_HPP

# define WINDOW_WIDTH 1056
# define WINDOW_HEIGHT 736

# define TILE_SIZE 32
# define PLAYER_SIZE 16

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

	// something else...?
};


#endif