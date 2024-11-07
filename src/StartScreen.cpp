#include "StartScreen.hpp"

/*
	CONSTRUCTOR
*/

StartScreen::StartScreen()
{
	if (!m_pixelFont.loadFromFile("assets/pixelfont.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

	m_title.setFont(m_pixelFont);
	m_title.setFillColor({235, 168, 14});
	m_title.setCharacterSize(50);
	m_title.setString("GRAVITY CHANGER");
	m_title.setPosition(GAME_WIDTH / 2 - 260, GAME_HEIGHT / 2 - 200);

	m_titleBG.setSize({535, 80});
	m_titleBG.setFillColor(sf::Color::Transparent);
	m_titleBG.setPosition(GAME_WIDTH / 2 - 280, GAME_HEIGHT / 2 - 210);

	m_pressEnter.setFont(m_pixelFont);
	m_pressEnter.setFillColor({235, 168, 14});
	m_pressEnter.setCharacterSize(20);
	m_pressEnter.setString("Press Enter to start");
	m_pressEnter.setPosition(GAME_WIDTH / 2 - m_pressEnter.getGlobalBounds().width / 2, GAME_HEIGHT / 2 + 100);

	m_moveSpeed = 80;

	// Animated shapes around the game title
	animatedShape	tempShape;
	sf::Vector2f	tempCoord;
	tempShape.shape.setSize({TILE_SIZE, TILE_SIZE});
	tempShape.shape.setFillColor({235, 168, 14});

	for (int i = 0; i < 4; ++i)
	{
		tempCoord = m_titleBG.getPosition();
		switch (i)
		{
			case 0:
				tempCoord.x += (m_titleBG.getSize().x / 2) - (TILE_SIZE / 2);
				tempCoord.y -= TILE_SIZE;
				tempShape.dirVec = {1, 0};
				break ;
			case 1:
				tempCoord.x += m_titleBG.getSize().x;
				tempCoord.y += (m_titleBG.getSize().y / 2) - (TILE_SIZE / 2);
				tempShape.dirVec = {0, 1};
				break ;
			case 2:
				tempCoord.x += (m_titleBG.getSize().x / 2) - (TILE_SIZE / 2);
				tempCoord.y += m_titleBG.getSize().y;
				tempShape.dirVec = {-1, 0};
				break ;	
			case 3:
				tempCoord.x -= TILE_SIZE;
				tempCoord.y += (m_titleBG.getSize().y / 2) - (TILE_SIZE / 2);
				tempShape.dirVec = {0, -1};
				break ;

			default:
				break ;
		}
		tempShape.shape.setPosition(tempCoord);

		m_animatedShapeArr[i] = tempShape;
	}

	// Turning points for tiles, index 0 = left top corner
	sf::Vector2f m_titleBgPos = m_titleBG.getPosition();
	m_turningPointArr[0].x = m_titleBgPos.x - TILE_SIZE;
	m_turningPointArr[0].y = m_titleBgPos.y - TILE_SIZE;
	m_turningPointArr[1].x = m_titleBgPos.x + m_titleBG.getSize().x;
	m_turningPointArr[1].y = m_titleBgPos.y - TILE_SIZE;
	m_turningPointArr[2].x = m_titleBgPos.x + m_titleBG.getSize().x;
	m_turningPointArr[2].y = m_titleBgPos.y + m_titleBG.getSize().y;
	m_turningPointArr[3].x = m_titleBgPos.x - TILE_SIZE;
	m_turningPointArr[3].y = m_titleBgPos.y + m_titleBG.getSize().y;
}

/*
	UPDATE
*/

void	StartScreen::updateScreen(float dt)
{
	sf::Vector2f newPos;

	for (animatedShape &tempShape : m_animatedShapeArr)
	{
		newPos.x = tempShape.shape.getPosition().x + (m_moveSpeed * dt * tempShape.dirVec.x);
		newPos.y = tempShape.shape.getPosition().y + (m_moveSpeed * dt * tempShape.dirVec.y);

		if (tempShape.dirVec.y == -1 && newPos.y <= m_turningPointArr[0].y)
		{
			newPos.y = m_turningPointArr[0].y;
			tempShape.dirVec.x = 1;
			tempShape.dirVec.y = 0;
		}
		else if (tempShape.dirVec.x == 1 && newPos.x >= m_turningPointArr[1].x)
		{
			newPos.x = m_turningPointArr[1].x;
			tempShape.dirVec.x = 0;
			tempShape.dirVec.y = 1;
		}
		else if (tempShape.dirVec.y == 1 && newPos.y >= m_turningPointArr[2].y)
		{
			newPos.y = m_turningPointArr[2].y;
			tempShape.dirVec.x = -1;
			tempShape.dirVec.y = 0;
		}
		else if (tempShape.dirVec.x == -1 && newPos.x <= m_turningPointArr[3].x)
		{
			newPos.x = m_turningPointArr[3].x;
			tempShape.dirVec.x = 0;
			tempShape.dirVec.y = -1;
		}

		tempShape.shape.setPosition(newPos);
	}
}

/*
	DRAW
*/

void	StartScreen::drawScreen(sf::RenderWindow &window, float dt)
{
	window.draw(m_titleBG);
	window.draw(m_title);
	window.draw(m_pressEnter);

	for (animatedShape &temp : m_animatedShapeArr)
	{
		updateScreen(dt);
		window.draw(temp.shape);
	}
}

