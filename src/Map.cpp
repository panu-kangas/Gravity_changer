#include "Map.hpp"

/*
	CONSTRUCTOR
*/

Map::Map()
{
	wallSprite.setFillColor({235, 168, 14}); // sort of orange
	wallSprite.setSize({TILE_SIZE, TILE_SIZE});

}


/*
	INIT MAP
*/

void	Map::initMap()
{

	readMap();
}


/*
	READ MAP
*/

void	Map::readMap()
{
	// add map file reading here

	mapTile tempTile;
	std::vector<mapTile> tempVec;

	for (int y = 0; y < WINDOW_HEIGHT; y += TILE_SIZE)
	{
		for (int x = 0; x < WINDOW_WIDTH; x += TILE_SIZE)
		{
			if (y > 608)
				tempTile.type = WALL;
			else
				tempTile.type = EMPTY;

			if (y == 576 && x == 576)
				tempTile.type = WALL;

			tempVec.push_back(tempTile);
		}
		tileVec.push_back(tempVec);
		tempVec.clear();
	}


}


/*
	DRAW MAP
*/


void	Map::drawMap(sf::RenderWindow &window)
{
	for (int y = 0; y < tileVec.size(); y++)
	{
		for (int x = 0; x < tileVec[y].size(); x++)
		{
			if (tileVec[y][x].type == WALL)
			{
				wallSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				window.draw(wallSprite);
			}
		}
	}
}



/*
	GETTERS
*/

std::vector<std::vector<mapTile>>	&Map::getTileVec()
{
	return (tileVec);
}

int			&Map::getTileType(int x, int y)
{
	return (tileVec[y][x].type);
}



