#ifndef INFOSCREEN_HPP
# define INFOSCREEN_HPP

# include <iostream>
# include "Constants.hpp"

class InfoScreen
{
	private:

	sf::Vector2f		coord;
	sf::Vector2f		size;
	sf::RectangleShape	background;

	sf::Text			scoreText;
	sf::Text			gameTimerText;
	sf::Text			gravityTimerText;
	sf::Font			pixelFont;

	sf::Clock			gameClock;
	float				curGameTime;

	sf::RectangleShape	gravityMeter;

	int		scoreCount;

	public:

	InfoScreen();
	~InfoScreen() {};

	void	drawInfoScreen(sf::RenderWindow &window);

	void	addScore(unsigned int addition);
	void	update(float gravityTime);

	void	resetInfo();

	float	getCurGameTime();
	int		getScore();


};


#endif