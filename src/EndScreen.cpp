#include "EndScreen.hpp"

/*
	CONSTRUCTOR
*/

EndScreen::EndScreen()
{
	if (!m_pixelFont.loadFromFile("assets/pixelfont.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

	m_yourScoreString = "";

	m_endText.setFont(m_pixelFont);
	m_endText.setCharacterSize(70);
	m_endText.setFillColor({235, 168, 14});
	m_endText.setString("GAME OVER");
	m_endText.setPosition(0, 0);

	m_yourScoreText.setFont(m_pixelFont);
	m_yourScoreText.setCharacterSize(40);
	m_yourScoreText.setFillColor({235, 168, 14});
	m_yourScoreText.setPosition(0, 0);

	m_pressEnter.setFont(m_pixelFont);
	m_pressEnter.setCharacterSize(20);
	m_pressEnter.setFillColor({235, 168, 14});
	m_pressEnter.setString("Press Enter to play again");
	m_pressEnter.setPosition(0, 0);
}

/*
	SCORE STRING
*/

void	EndScreen::setScoreString(int score)
{
	m_yourScoreString = "Your score:\n" + std::to_string(score);
	m_yourScoreText.setString(m_yourScoreString);


}

/*
	DRAW
*/


void	EndScreen::draw(sf::RenderWindow &window)
{
	if (m_endText.getPosition().x == 0)
	{
		m_endText.setPosition((GAME_WIDTH / 2) - (m_endText.getGlobalBounds().width / 2), 
		(GAME_HEIGHT / 2) - (m_endText.getGlobalBounds().height / 2) - 200);

		m_yourScoreText.setPosition((GAME_WIDTH/ 2) - (m_yourScoreText.getGlobalBounds().width / 2), 
		(GAME_HEIGHT / 2) - (m_yourScoreText.getGlobalBounds().height / 2) + 50);

		m_pressEnter.setPosition(GAME_WIDTH / 2 - m_pressEnter.getGlobalBounds().width / 2,
		GAME_HEIGHT / 2 - m_pressEnter.getGlobalBounds().height / 2 + 200);
	}

	window.draw(m_endText);
	window.draw(m_yourScoreText);
	window.draw(m_pressEnter);
}

/*
	GETTERS
*/

std::string	&EndScreen::getScoreString()
{
	return (m_yourScoreString);
}


