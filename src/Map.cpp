#include "Map.hpp"
#include <fstream> 

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
	std::ifstream	inputFile("assets/map.txt");
	std::string		tempStr = "";
	std::string		mapStr = "";
	int				rowLen = 0;
	int				mapHeightCounter = 0;

	if (!inputFile.is_open())
	{
		std::cerr << "\nMap-file error: could not open file.\nExiting program.\n" << std::endl;
		exit (1);
	}

	while (std::getline(inputFile, tempStr))
	{
		if (mapStr.empty())
			rowLen = tempStr.length();
		
		if (rowLen == tempStr.length())
			mapStr += tempStr;
		else
		{
			std::cerr << "\nMap-file error: given map is not rectangular\nExiting program.\n" << std::endl;
			exit (1);
		}
		mapHeightCounter++;
	}

	if (mapStr.empty())
	{
		std::cerr << "\nMap-file error: empty mapfile given.\nExiting program.\n" << std::endl;
		exit (1);
	}
	else if (rowLen != 33 || mapHeightCounter != 23)
	{
		std::cerr << "\nMap-file error: map has to be 33x23 tiles.\nExiting program.\n" << std::endl;
		exit (1);
	}

	setTileVec(mapStr, rowLen);
}

void	Map::setTileVec(std::string mapStr, int rowLen)
{
	int			k = 0;
	mapTile		tile;
	std::string	ValidMapCharacters = VALID_MAP_CHAR;
	std::vector<mapTile> tempVec;

	for (int i = 0; i < mapStr.length(); ++i)
	{
		if (ValidMapCharacters.find_first_of(mapStr[i]) == ValidMapCharacters.npos)
		{
			std::cerr << "\nMap-file error: map has invalid character(s).\n" << "Exiting program.\n" << std::endl;
			exit (1);
		}

		tile.type = mapStr[i];
		tile.shape.setSize({TILE_SIZE, TILE_SIZE});
		if (tile.type == '1')
		{
			tile.type = WALL;
			tile.shape.setFillColor({235, 168, 14});
		}
		else if (tile.type == '0')
		{
			tile.type = EMPTY;
			tile.shape.setFillColor(sf::Color::Black);
		}

		tempVec.push_back(tile);
		k++;
		if (k == rowLen)
		{
			m_tileVec.push_back(tempVec);
			tempVec.clear();
			k = 0;
		}
	}
}

/*
	DRAW MAP
*/

void	Map::drawMap(sf::RenderWindow &window)
{
	for (int y = 0; y < m_tileVec.size(); ++y)
	{
		for (int x = 0; x < m_tileVec[y].size(); ++x)
		{
			if (m_tileVec[y][x].type == WALL)
			{
				m_tileVec[y][x].shape.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				window.draw(m_tileVec[y][x].shape);
			}
		}
	}
}

/*
	GETTERS
*/

std::vector<std::vector<mapTile>>	&Map::getTileVec()
{
	return (m_tileVec);
}

int			&Map::getTileType(int x, int y)
{
	return (m_tileVec[y][x].type);
}



