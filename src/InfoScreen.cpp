#include "InfoScreen.hpp"
#include <string>
#include <iomanip>
#include <sstream>
#include <math.h>

/*
	CONSTRUCTOR
*/

InfoScreen::InfoScreen()
{
	m_size.x = 500;
	m_size.y = 70;
	m_coord.x = (GAME_WIDTH / 2) - (m_size.x / 2);
	m_coord.y = GAME_HEIGHT - m_size.y - 10;
	m_background.setSize(m_size);
	m_background.setPosition(m_coord);
	m_background.setFillColor(sf::Color::Black);

	if (!m_pixelFont.loadFromFile("assets/pixelfont.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

	// Score
	m_scoreText.setFont(m_pixelFont);
	m_scoreText.setFillColor({235, 168, 14});
	m_scoreText.setCharacterSize(20);
	m_scoreText.setPosition(m_coord.x + 2, m_coord.y + 2);
	m_scoreText.setString("SCORE:\n0");
	m_scoreCount = 0;

	// Game timer
	m_gameTimerText.setFont(m_pixelFont);
	m_gameTimerText.setFillColor({235, 168, 14});
	m_gameTimerText.setCharacterSize(20);
	m_gameTimerText.setPosition(m_coord.x + 150, m_coord.y + 2);
	m_gameTimerText.setString("TIME LEFT:\n30:00");
	m_curGameTime = 20.0;

	// Gravity timer
	m_gravityTimerText.setFont(m_pixelFont);
	m_gravityTimerText.setFillColor({235, 168, 14});
	m_gravityTimerText.setCharacterSize(20);
	m_gravityTimerText.setPosition(m_coord.x + 300, m_coord.y + 2);
	m_gravityTimerText.setString("GRAVITY CHANGE:\n");

	m_gravityMeter.setFillColor(sf::Color::Green);
	m_gravityMeter.setPosition(m_coord.x + 300, m_coord.y + 32);
	m_gravityMeter.setSize({185, 10});
}

/*
	DRAW
*/

void	InfoScreen::drawInfoScreen(sf::RenderWindow &window)
{
	window.draw(m_background);
	window.draw(m_scoreText);
	window.draw(m_gameTimerText);
	window.draw(m_gravityTimerText);
	window.draw(m_gravityMeter);
}

/*
	SCORE FUNCTIONS
*/

void	InfoScreen::addScore(unsigned int addition)
{
	m_scoreCount += addition;

	std::string scoreString;
	scoreString = "SCORE\n" + std::to_string(m_scoreCount);
	m_scoreText.setString(scoreString);

	m_curGameTime += 2;
	if (m_curGameTime > 30)
		m_curGameTime = 30;
}

/*
	TIMER FUNCTIONS
*/

void	InfoScreen::update(float gravityTime)
{
	// TIMER
	m_curGameTime -= m_gameClock.getElapsedTime().asSeconds();
	m_gameClock.restart();
	if (m_curGameTime < 0)
		m_curGameTime = 0;

	float	seconds;
	seconds = (m_curGameTime - floor(m_curGameTime)) * 60;

	std::stringstream	stream;
	std::string			timerString;

	stream << std::fixed << std::setprecision(0) << floor(m_curGameTime) << ":" << floor(seconds);
	timerString = "TIME LEFT:\n" + stream.str();
	m_gameTimerText.setString(timerString);

	// GRAVITY METER
	float	len;
	len = (gravityTime / GRAVITY_RECHARGE) * 185;
	if (len >= 185)
	{
		len = 185;
		m_gravityMeter.setFillColor(sf::Color::Green);
	}
	else
		m_gravityMeter.setFillColor(sf::Color::White);
	m_gravityMeter.setSize({len, 10});
}

void	InfoScreen::resetInfo()
{
	m_scoreCount = 0;
	m_curGameTime = 20.0;
	m_scoreText.setString("SCORE:\n0");
	m_gameClock.restart();
}

float	InfoScreen::getCurGameTime()
{
	return (m_curGameTime);
}

int		InfoScreen::getScore()
{
	return (m_scoreCount);
}

