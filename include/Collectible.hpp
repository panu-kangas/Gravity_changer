#ifndef COLLECTIBLE_HPP
# define COLLECTIBLE_HPP

# include <cstdlib> // for rand() and srand()
# include <ctime> // for time() that srand uses as seed

# include "Constants.hpp"
# include "Map.hpp"
# include "Player.hpp"

class Collectible
{
	private:

	sf::Vector2f		m_coord;
	sf::RectangleShape	m_sprite;
	bool				m_coordinateSet;

	void	setNewCoord(int x, int y, int direction, Player &player);
	bool	checkAdjacentPlayer(Player &player, int x, int y);

//////

	public:

	Collectible();
	~Collectible() {};

	void	createNewCollectible(Map &map, Player &player);

	void	drawCollectible(sf::RenderWindow &window);

	sf::Vector2f		getCoord();
	sf::RectangleShape	&getSprite();

};

#endif