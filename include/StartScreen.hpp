#ifndef STARTSCREEN_HPP
# define STARTSCREEN_HPP

# include <iostream>
# include "Constants.hpp"

struct animatedShape
{
	sf::RectangleShape	shape;
	sf::Vector2f		dirVec;
};

class StartScreen
{
	private:

	sf::Font	pixelFont;

	sf::Text			title;
	sf::RectangleShape	titleBG;

	sf::Text	pressEnter;

	animatedShape	animatedShapeArr[4];
	sf::Vector2f	turningPointArr[4];

	int		moveSpeed;


	public:

	StartScreen();
	~StartScreen() {};

	void	drawScreen(sf::RenderWindow &window, float dt);
	void	updateScreen(float dt);

};


#endif