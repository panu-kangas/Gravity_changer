#include "Map.hpp"

/*
	CONSTRUCTOR
*/

Map::Map()
{

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
			if (y > 608 || y == 0 \
			|| x == 0 || x == WINDOW_WIDTH - TILE_SIZE \
			|| (y == 32 && x == 160) \
			|| (y == 64 && x == 192)
			|| (y == 576 && x == 192) \
			|| (y == 608 && x == 160))
			{
				tempTile.type = WALL;
				tempTile.shape.setSize({TILE_SIZE, TILE_SIZE});
				tempTile.shape.setFillColor({235, 168, 14});
			}
			else
				tempTile.type = EMPTY;
				
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
				tileVec[y][x].shape.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				window.draw(tileVec[y][x].shape);
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



