#ifndef ENDSCREEN_HPP
# define ENDSCREEN_HPP

# include <iostream>
# include "Constants.hpp"

class EndScreen
{
	private:

	sf::Text	m_endText;
	sf::Text	m_yourScoreText;
	sf::Text	m_pressEnter;
	sf::Font	m_pixelFont;
	std::string	m_yourScoreString;

//////

	public:

	EndScreen();
	~EndScreen() {};

	void	setScoreString(int score);
	void	draw(sf::RenderWindow &window);

	std::string	&getScoreString();

};

#endif