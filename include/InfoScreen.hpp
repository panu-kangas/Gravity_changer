#ifndef INFOSCREEN_HPP
# define INFOSCREEN_HPP

# include <iostream>
# include "Constants.hpp"

class InfoScreen
{
	private:

	sf::Vector2f		m_coord;
	sf::Vector2f		m_size;
	sf::RectangleShape	m_background;
	sf::Text			m_scoreText;
	sf::Text			m_gameTimerText;
	sf::Text			m_gravityTimerText;
	sf::Font			m_pixelFont;
	sf::Clock			m_gameClock;
	sf::RectangleShape	m_gravityMeter;

	float	m_curGameTime;
	int		m_scoreCount;

//////

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