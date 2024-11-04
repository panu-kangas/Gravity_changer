#include "StartScreen.hpp"


/*
	CONSTRUCTOR
*/

StartScreen::StartScreen()
{
	if (!pixelFont.loadFromFile("assets/pixelfont.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

	title.setFont(pixelFont);
	title.setFillColor({235, 168, 14});
	title.setCharacterSize(50);
	title.setString("GRAVITY CHANGER");
	title.setPosition(GAME_WIDTH / 2 - 260, GAME_HEIGHT / 2 - 200);

	// NOT NEEDED! Use title.getGlobalBounds() instead
	titleBG.setSize({535, 80});
	titleBG.setFillColor(sf::Color::Transparent);
	titleBG.setPosition(GAME_WIDTH / 2 - 280, GAME_HEIGHT / 2 - 210);

	pressEnter.setFont(pixelFont);
	pressEnter.setFillColor({235, 168, 14});
	pressEnter.setCharacterSize(20);
	pressEnter.setString("Press Enter to start");
	pressEnter.setPosition(GAME_WIDTH / 2 - pressEnter.getGlobalBounds().width / 2, 
	GAME_HEIGHT / 2 + 100);

	moveSpeed = 80;

	// Animated shapes around the title

	animatedShape tempShape;

	for (int i = 0; i < 4; ++i)
	{
		tempShape.shape.setSize({TILE_SIZE, TILE_SIZE});
		tempShape.shape.setFillColor({235, 168, 14});

		sf::Vector2f	tempCoord;
		tempCoord = titleBG.getPosition();

		switch (i)
		{
			case 0:
				tempCoord.x += (titleBG.getSize().x / 2) - (TILE_SIZE / 2);
				tempCoord.y -= TILE_SIZE;
				tempShape.shape.setPosition(tempCoord);
				tempShape.dirVec = {1, 0};
				break ;
			case 1:
				tempCoord.x += titleBG.getSize().x;
				tempCoord.y += (titleBG.getSize().y / 2) - (TILE_SIZE / 2);
				tempShape.shape.setPosition(tempCoord);
				tempShape.dirVec = {0, 1};
				break ;
			case 2:
				tempCoord.x += (titleBG.getSize().x / 2) - (TILE_SIZE / 2);
				tempCoord.y += titleBG.getSize().y;
				tempShape.shape.setPosition(tempCoord);
				tempShape.dirVec = {-1, 0};
				break ;	
			case 3:
				tempCoord.x -= TILE_SIZE;
				tempCoord.y += (titleBG.getSize().y / 2) - (TILE_SIZE / 2);
				tempShape.shape.setPosition(tempCoord);
				tempShape.dirVec = {0, -1};
				break ;	
			default:
				break ;
		}

		animatedShapeArr[i] = tempShape;
	}


	// Turning points for tiles

	sf::Vector2f titleBgPos = titleBG.getPosition();

	turningPointArr[0].x = titleBgPos.x - TILE_SIZE;
	turningPointArr[0].y = titleBgPos.y - TILE_SIZE;
	turningPointArr[1].x = titleBgPos.x + titleBG.getSize().x;
	turningPointArr[1].y = titleBgPos.y - TILE_SIZE;
	turningPointArr[2].x = titleBgPos.x + titleBG.getSize().x;
	turningPointArr[2].y = titleBgPos.y + titleBG.getSize().y;
	turningPointArr[3].x = titleBgPos.x - TILE_SIZE;
	turningPointArr[3].y = titleBgPos.y + titleBG.getSize().y;


}

/*
	UPDATE
*/

void	StartScreen::updateScreen(float dt)
{
	sf::Vector2f newPos;

	for (animatedShape &temp : animatedShapeArr)
	{
		newPos.x = temp.shape.getPosition().x + (moveSpeed * dt * temp.dirVec.x);
		newPos.y = temp.shape.getPosition().y + (moveSpeed * dt * temp.dirVec.y);

		if (temp.dirVec.y == -1 && newPos.y <= turningPointArr[0].y)
		{
			newPos.y = turningPointArr[0].y;
			temp.dirVec.x = 1;
			temp.dirVec.y = 0;
		}
		else if (temp.dirVec.x == 1 && newPos.x >= turningPointArr[1].x)
		{
			newPos.x = turningPointArr[1].x;
			temp.dirVec.x = 0;
			temp.dirVec.y = 1;
		}
		else if (temp.dirVec.y == 1 && newPos.y >= turningPointArr[2].y)
		{
			newPos.y = turningPointArr[2].y;
			temp.dirVec.x = -1;
			temp.dirVec.y = 0;
		}
		else if (temp.dirVec.x == -1 && newPos.x <= turningPointArr[3].x)
		{
			newPos.x = turningPointArr[3].x;
			temp.dirVec.x = 0;
			temp.dirVec.y = -1;
		}

		temp.shape.setPosition(newPos);
	}

}


/*
	DRAW
*/

void	StartScreen::drawScreen(sf::RenderWindow &window, float dt)
{
	window.draw(titleBG);
	window.draw(title);
	window.draw(pressEnter);

	for (animatedShape &temp : animatedShapeArr)
	{
		updateScreen(dt);
		window.draw(temp.shape);
	}
}

