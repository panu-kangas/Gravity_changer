#ifndef MAP_HPP
# define MAP_HPP

# include <SFML/Graphics.hpp>
# include <iostream>
# include <vector>

# include "Constants.hpp"


class Map
{
	private:

	sf::RectangleShape	wallSprite;

	std::vector<std::vector<mapTile>>	tileVec;


	public:

	Map();
	~Map() {};

	void	initMap();
	void	readMap();

	void	drawMap(sf::RenderWindow &window);

	std::vector<std::vector<mapTile>>	&getTileVec();
	int			&getTileType(int x, int y);

};





#endif