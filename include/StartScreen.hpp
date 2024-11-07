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

	sf::Font			m_pixelFont;
	sf::Text			m_title;
	sf::RectangleShape	m_titleBG; // BG = Background
	sf::Text			m_pressEnter;
	sf::Vector2f		m_turningPointArr[4];
	animatedShape		m_animatedShapeArr[4];

	int		m_moveSpeed;

//////

	public:

	StartScreen();
	~StartScreen() {};

	void	drawScreen(sf::RenderWindow &window, float dt);
	void	updateScreen(float dt);
};

#endif