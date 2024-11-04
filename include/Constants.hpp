#ifndef CONSTANTS_HPP
# define CONSTANTS_HPP

# define GAME_WIDTH 1056
# define GAME_HEIGHT 736

# define TILE_SIZE 32
# define PLAYER_SIZE 16
# define COLLECT_SIZE 12

# define VALID_MAP_CHAR	"10"

# include <SFML/Graphics.hpp> // this might not be a good place for this...?


enum direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum keys
{
	W,
	A,
	S,
	D,
	UPARR,
	DOWNARR,
	LEFTARR,
	RIGHTARR
};

enum tiletype
{
	EMPTY,
	WALL
};

enum gamestates
{
	STARTSCREEN,
	GAME,
	END
};

struct mapTile
{
	int	type;
	sf::RectangleShape	shape;

	// something else...?
};


#endif