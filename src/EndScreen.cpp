#include "EndScreen.hpp"

/*
	CONSTRUCTOR
*/

EndScreen::EndScreen()
{
	if (!pixelFont.loadFromFile("assets/pixelfont.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

	yourScoreString = "";

	endText.setFont(pixelFont);
	endText.setCharacterSize(70);
	endText.setFillColor({235, 168, 14});
	endText.setString("GAME OVER");
	endText.setPosition(0, 0);

	yourScoreText.setFont(pixelFont);
	yourScoreText.setCharacterSize(40);
	yourScoreText.setFillColor({235, 168, 14});
	yourScoreText.setPosition(0, 0);

	pressEnter.setFont(pixelFont);
	pressEnter.setCharacterSize(20);
	pressEnter.setFillColor({235, 168, 14});
	pressEnter.setString("Press Enter to play again");
	pressEnter.setPosition(0, 0);
}

/*
	SCORE STRING
*/

void	EndScreen::setScoreString(int score)
{
	yourScoreString = "Your score:\n" + std::to_string(score);
	yourScoreText.setString(yourScoreString);


}


/*
	DRAW
*/


void	EndScreen::draw(sf::RenderWindow &window)
{

	if (endText.getPosition().x == 0)
	{
		endText.setPosition((GAME_WIDTH / 2) - (endText.getGlobalBounds().width / 2), 
		(GAME_HEIGHT / 2) - (endText.getGlobalBounds().height / 2) - 200);

		yourScoreText.setPosition((GAME_WIDTH/ 2) - (yourScoreText.getGlobalBounds().width / 2), 
		(GAME_HEIGHT / 2) - (yourScoreText.getGlobalBounds().height / 2) + 50);

		pressEnter.setPosition(GAME_WIDTH / 2 - pressEnter.getGlobalBounds().width / 2,
		GAME_HEIGHT / 2 - pressEnter.getGlobalBounds().height / 2 + 200);
	}

	window.draw(endText);
	window.draw(yourScoreText);
	window.draw(pressEnter);
}


/*
	GETTERS
*/

std::string	&EndScreen::getScoreString()
{
	return (yourScoreString);
}


