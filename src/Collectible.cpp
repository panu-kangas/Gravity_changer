#include "Collectible.hpp"


/*
	CONSTRUCTOR
*/

Collectible::Collectible()
{
	coord.x = 0; // should these be -10 or something...?
	coord.y = 0;

	coordinateSet = false;

	sprite.setSize({COLLECT_SIZE, COLLECT_SIZE});
	sprite.setFillColor(sf::Color::Red);
	sprite.setPosition(coord);
}


/*
	CREATE COLLECTIBLE
*/

void	Collectible::createNewCollectible(Map &map, Player &player)
{
	std::vector<std::vector<mapTile>>	&tileVec = map.getTileVec();
	int		x, y, side;

	srand(time(NULL));
	sprite.setPosition({0, 0});

	// Should here be a safety system for faulty maps...? 
	// For example a counter, that breaks the loop if it goes over 100?
	while (1)
	{
		x = rand() % (GAME_WIDTH / TILE_SIZE);
		y = rand() % (GAME_HEIGHT / TILE_SIZE);

		if (tileVec[y][x].type == WALL && !checkAdjacentPlayer(player, x, y))
		{
			if (x > 0 && tileVec[y][x - 1].type == EMPTY)
				break ;
			else if (x < (GAME_WIDTH / TILE_SIZE - 1) && tileVec[y][x + 1].type == EMPTY)
				break ;
			else if (y > 0 && tileVec[y - 1][x].type == EMPTY)
				break ;
			else if (y < (GAME_HEIGHT / TILE_SIZE - 1) && tileVec[y + 1][x].type == EMPTY)
				break ;
		}
	}

	// Should here be a safety system for faulty maps etc...? 
	// For example a counter, that breaks the loop if it goes over 100 and throws error?
	while (1)
	{
		side = rand() % 4;
		switch (side)
		{
			case UP :
				if (y > 0 && tileVec[y - 1][x].type == EMPTY)
					setNewCoord(x, y, UP, player);
				break ;
			
			case DOWN :
				if (y < (GAME_HEIGHT / TILE_SIZE - 1) && tileVec[y + 1][x].type == EMPTY)
					setNewCoord(x, y, DOWN, player);
				break ;

			case LEFT :
				if (x > 0 && tileVec[y][x - 1].type == EMPTY)
					setNewCoord(x, y, LEFT, player);
				break ;

			case RIGHT :
				if (x < (GAME_WIDTH / TILE_SIZE - 1) && tileVec[y][x + 1].type == EMPTY)
					setNewCoord(x, y, RIGHT, player);
				break ;

			default :
				continue;
		}


		if (coordinateSet == true)
		{
			coordinateSet = false;
			break ;
		}
	}

}

bool	Collectible::checkAdjacentPlayer(Player &player, int x, int y)
{
	sf::Vector2i playerTileCoord;

	playerTileCoord.x = player.getCoord().x / TILE_SIZE;
	playerTileCoord.y = player.getCoord().y / TILE_SIZE;

	if (playerTileCoord.x == x - 1 || playerTileCoord.x == x + 1
	|| playerTileCoord.y == y - 1 || playerTileCoord.y == y + 1)
		return (true);
	else
		return (false);
}



void	Collectible::setNewCoord(int x, int y, int direction, Player &player)
{
	if (direction == UP)
	{
		coord.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
		coord.y = (y * TILE_SIZE) - COLLECT_SIZE;
	}
	else if (direction == DOWN)
	{
		coord.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
		coord.y = (y * TILE_SIZE) + TILE_SIZE;
	}
	else if (direction == LEFT)
	{
		coord.x = (x * TILE_SIZE) - COLLECT_SIZE;
		coord.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	}
	else if (direction == RIGHT)
	{
		coord.x = (x * TILE_SIZE) + TILE_SIZE;
		coord.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	}

	sprite.setPosition(coord);
	coordinateSet = true;
}



/*
	DRAW
*/


void	Collectible::drawCollectible(sf::RenderWindow &window)
{
	window.draw(sprite);
}




/*
	GETTERS
*/


sf::Vector2f	Collectible::getCoord()
{
	return (coord);
}

sf::RectangleShape	&Collectible::getSprite()
{
	return (sprite);
}

