#ifndef ENDSCREEN_HPP
# define ENDSCREEN_HPP

# include <iostream>
# include "Constants.hpp"

class EndScreen
{
	private:

	sf::Text	endText;
	sf::Text	yourScoreText;
	sf::Text	pressEnter;
	sf::Font	pixelFont;
	
	std::string	yourScoreString;

	public:

	EndScreen();
	~EndScreen() {};

	void	setScoreString(int score);
	void	draw(sf::RenderWindow &window);

	std::string	&getScoreString();

};

#endif