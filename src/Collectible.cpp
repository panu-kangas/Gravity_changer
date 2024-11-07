#include "Collectible.hpp"

/*
	CONSTRUCTOR
*/

Collectible::Collectible()
{
	m_coord.x = 0;
	m_coord.y = 0;

	m_coordinateSet = false;

	m_sprite.setSize({COLLECT_SIZE, COLLECT_SIZE});
	m_sprite.setFillColor(sf::Color::Red);
	m_sprite.setPosition(m_coord);
}


/*
	CREATE COLLECTIBLE
*/

// A safety system in the while(1) -loops in case of faulty maps...? For example a counter, that breaks the loop if it goes over 100?

void	Collectible::createNewCollectible(Map &map, Player &player)
{
	std::vector<std::vector<mapTile>>	&tileVec = map.getTileVec();
	int		x, y, side;

	srand(time(NULL));
	m_sprite.setPosition({0, 0});

	// Find random map-tile on map
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

	// Get random side of the map-tile
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

		if (m_coordinateSet == true)
		{
			m_coordinateSet = false;
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
		m_coord.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
		m_coord.y = (y * TILE_SIZE) - COLLECT_SIZE;
	}
	else if (direction == DOWN)
	{
		m_coord.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
		m_coord.y = (y * TILE_SIZE) + TILE_SIZE;
	}
	else if (direction == LEFT)
	{
		m_coord.x = (x * TILE_SIZE) - COLLECT_SIZE;
		m_coord.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	}
	else if (direction == RIGHT)
	{
		m_coord.x = (x * TILE_SIZE) + TILE_SIZE;
		m_coord.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	}

	m_sprite.setPosition(m_coord);
	m_coordinateSet = true;
}


/*
	DRAW
*/


void	Collectible::drawCollectible(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}


/*
	GETTERS
*/


sf::Vector2f	Collectible::getCoord()
{
	return (m_coord);
}

sf::RectangleShape	&Collectible::getSprite()
{
	return (m_sprite);
}

