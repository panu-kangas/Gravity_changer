#ifndef COLLECTIBLE_HPP
# define COLLECTIBLE_HPP

# include <cstdlib>
# include <ctime>

# include "Constants.hpp"
# include "Map.hpp"
# include "Player.hpp"

class Collectible
{
	private:

	sf::Vector2f		coord;
	sf::RectangleShape	sprite;

	bool	coordinateSet;


	void	setNewCoord(int x, int y, int direction, Player &player);


	public:

	Collectible();
	~Collectible() {};

	void	createNewCollectible(Map &map, Player &player);

	void	drawCollectible(sf::RenderWindow &window);

	sf::Vector2f		getCoord();
	sf::RectangleShape	&getSprite();

};

#endif