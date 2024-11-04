#include "InfoScreen.hpp"
#include <string>


/*
	CONSTRUCTOR
*/

InfoScreen::InfoScreen()
{

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

	scoreText.setFont(pixelFont);
	scoreText.setFillColor({235, 168, 14});
	scoreText.setCharacterSize(20);
	scoreText.setPosition(coord.x + 2, coord.y + 2);
	scoreText.setString("SCORE:\n0");

	scoreCount = 0;

	gameTimer.setFont(pixelFont);
	gameTimer.setFillColor({235, 168, 14});
	gameTimer.setCharacterSize(20);
	gameTimer.setPosition(coord.x + 150, coord.y + 2);
	gameTimer.setString("TIME LEFT:\n30:00");

}


/*
	DRAW
*/


void	InfoScreen::drawInfoScreen(sf::RenderWindow &window)
{
	window.draw(background);
	window.draw(scoreText);
	window.draw(gameTimer);
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

}

/*
	TIMER FUNCTIONS
*/

// NOT DONE
void	InfoScreen::updateTimer()
{
	std::string timerString;



}

