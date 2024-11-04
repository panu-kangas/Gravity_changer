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
	// Common info
	size.x = 500;
	size.y = 70;
	coord.x = (GAME_WIDTH / 2) - (size.x / 2);
	coord.y = GAME_HEIGHT - size.y - 10;
	background.setSize(size);
	background.setPosition(coord);
	background.setFillColor(sf::Color::Black); // something else maybe? Black is boring...

	if (!pixelFont.loadFromFile("assets/pixelfont.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

	// Score
	scoreText.setFont(pixelFont);
	scoreText.setFillColor({235, 168, 14});
	scoreText.setCharacterSize(20);
	scoreText.setPosition(coord.x + 2, coord.y + 2);
	scoreText.setString("SCORE:\n0");
	scoreCount = 0;

	// Game timer
	gameTimerText.setFont(pixelFont);
	gameTimerText.setFillColor({235, 168, 14});
	gameTimerText.setCharacterSize(20);
	gameTimerText.setPosition(coord.x + 150, coord.y + 2);
	gameTimerText.setString("TIME LEFT:\n30:00");
	curGameTime = 5.0;

	// Gravity timer
	gravityTimerText.setFont(pixelFont);
	gravityTimerText.setFillColor({235, 168, 14});
	gravityTimerText.setCharacterSize(20);
	gravityTimerText.setPosition(coord.x + 300, coord.y + 2);
	gravityTimerText.setString("GRAVITY CHANGE:\n");

	gravityMeter.setFillColor(sf::Color::Green);
	gravityMeter.setPosition(coord.x + 300, coord.y + 32);
	gravityMeter.setSize({185, 10});

}


/*
	DRAW
*/


void	InfoScreen::drawInfoScreen(sf::RenderWindow &window)
{
	window.draw(background);
	window.draw(scoreText);
	window.draw(gameTimerText);
	window.draw(gravityTimerText);
	window.draw(gravityMeter);
}



/*
	SCORE FUNCTIONS
*/

void	InfoScreen::addScore(unsigned int addition)
{
	scoreCount += addition;

	std::string scoreString;
	scoreString = "SCORE\n" + std::to_string(scoreCount);
	scoreText.setString(scoreString);

	curGameTime += 2;
}

/*
	TIMER FUNCTIONS
*/

void	InfoScreen::update(float gravityTime)
{
	// TIMER
	curGameTime -= gameClock.getElapsedTime().asSeconds();
	gameClock.restart();

	float	seconds;
	seconds = (curGameTime - floor(curGameTime)) * 60;

	std::stringstream	stream;
	std::string			timerString;

	stream << std::fixed << std::setprecision(0) << floor(curGameTime) << ":" << floor(seconds);
	timerString = "TIME LEFT:\n" + stream.str();
	gameTimerText.setString(timerString);

	// GRAVITY METER
	float	len;

	len = (gravityTime / 3) * 185;

	if (len >= 185)
	{
		len = 185;
		gravityMeter.setFillColor(sf::Color::Green);
	}
	else
		gravityMeter.setFillColor(sf::Color::White);

	gravityMeter.setSize({len, 10});
}

void	InfoScreen::restartGameClock()
{
	gameClock.restart();
}

float	InfoScreen::getCurGameTime()
{
	return (curGameTime);
}

