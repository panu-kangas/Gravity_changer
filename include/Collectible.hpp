#ifndef COLLECTIBLE_HPP
# define COLLECTIBLE_HPP

# include <cstdlib>
# include <ctime>

# include "Constants.hpp"
# include "Map.hpp"

class Collectible
{
	private:

	sf::Vector2f		coord;
	sf::RectangleShape	sprite;

	void	setNewCoord(int x, int y, int direction);


	public:

	Collectible();
	~Collectible() {};

	void	createNewCollectible(Map &map);

	void	drawCollectible(sf::RenderWindow &window);

	sf::Vector2f		getCoord();
	sf::RectangleShape	&getSprite();

};

#endif