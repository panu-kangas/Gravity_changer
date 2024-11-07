#include "GameHandler.hpp"

/*
	CONSTRUCTOR
*/

GameHandler::GameHandler()
{
	m_gravityVelocity = 0.05;
	m_gravityDir = DOWN;
	m_firstGravityChange = false;
	m_playerHasMoved = false;

	for (int i = 0; i < 8; ++i)
		m_pressedKeyArr[i] = false;
	for (int i = 0; i < 4; ++i)
		m_collisionFlagArr[i] = false;

	m_gameState = STARTSCREEN;
}

/*
	INITIALIZATION
*/

void	GameHandler::initGame()
{
	m_collectible.createNewCollectible(m_map, m_player);
	m_player.resetPlayer();
	m_info.resetInfo();
	m_end.getScoreString() = "";
	m_gravityDir = DOWN;
	m_firstGravityChange = false;
}

/*
	CHECK INPUT
*/

void	GameHandler::checkInput(sf::Event &event)
{
	// MOVEMENT
	switch (event.key.code)
	{
		case sf::Keyboard::W :
			if (m_gravityDir == DOWN && !m_player.getJumpState())
				m_player.setJumpState(true, W, false);			
			setKeypressState(true, W);
			break ;

		case sf::Keyboard::S :
			if (m_gravityDir == UP && !m_player.getJumpState())
				m_player.setJumpState(true, S, false);
			setKeypressState(true, S);
			break ;

		case sf::Keyboard::A :
			if (m_gravityDir == RIGHT && !m_player.getJumpState())
				m_player.setJumpState(true, A, false);
			setKeypressState(true, A);
			break ;

		case sf::Keyboard::D :
			if (m_gravityDir == LEFT && !m_player.getJumpState())
				m_player.setJumpState(true, D, false);
			setKeypressState(true, D);
			break ;

		default:
			break ;
	}

	// GRAVITY
	if (m_firstGravityChange && m_gravityClock.getElapsedTime().asSeconds() < GRAVITY_RECHARGE)
		return ;
	
	switch (event.key.code)
	{
		case sf::Keyboard::Up :
			if (m_pressedKeyArr[UPARR] == false && m_gravityDir != UP)
			{
				m_gravityDir = UP;
				setKeypressState(true, UPARR);
				m_player.setJumpState(true, UPARR, true);
				m_gravityClock.restart();
			}
			break ;
		
		case sf::Keyboard::Down :
			if (m_pressedKeyArr[DOWNARR] == false && m_gravityDir != DOWN)
			{
				m_gravityDir = DOWN;
				setKeypressState(true, DOWNARR);
				m_player.setJumpState(true, DOWNARR, true);
				m_gravityClock.restart();
			}
			break ;

		case sf::Keyboard::Left :
			if (m_pressedKeyArr[LEFTARR] == false && m_gravityDir != LEFT)
			{
				m_gravityDir = LEFT;
				setKeypressState(true, LEFTARR);
				m_player.setJumpState(true, LEFTARR, true);
				m_gravityClock.restart();
			}
			break ;

		case sf::Keyboard::Right :
			if (m_pressedKeyArr[RIGHTARR] == false && m_gravityDir != RIGHT)
			{
				m_gravityDir = RIGHT;
				setKeypressState(true, RIGHTARR);
				m_player.setJumpState(true, RIGHTARR, true);
				m_gravityClock.restart();
			}
			break ;

		default :
			break ;
	}

	if (!m_firstGravityChange && \
	(m_pressedKeyArr[UPARR] || m_pressedKeyArr[DOWNARR] || m_pressedKeyArr[LEFTARR] || m_pressedKeyArr[RIGHTARR]))
		m_firstGravityChange = true;
}

void	GameHandler::checkRelease(sf::Event &event)
{
	switch (event.key.code)
	{
		case sf::Keyboard::W :
			setKeypressState(false, W);
			break ;

		case sf::Keyboard::S :
			setKeypressState(false, S);
			break ;

		case sf::Keyboard::A :
			setKeypressState(false, A);
			break ;

		case sf::Keyboard::D :
			setKeypressState(false, D);
			break ;

		case sf::Keyboard::Up :
			setKeypressState(false, UPARR);
			break ;
		
		case sf::Keyboard::Down :
			setKeypressState(false, DOWNARR);
			break ;

		case sf::Keyboard::Left :
			setKeypressState(false, LEFTARR);
			break ;

		case sf::Keyboard::Right :
			setKeypressState(false, RIGHTARR);
			break ;

		default:
			break ;
	}
}

/*
	UPDATE GAME
*/

void	GameHandler::updateGame(float dt)
{
	if (m_info.getCurGameTime() <= 0)
	{
		m_gameState = END;
		return ;
	}

	handleSidewaysMovement();

	// Fixing the "falls in the start" -bug which randomly appears
	if (m_playerHasMoved == false && \
	(m_pressedKeyArr[W] || m_pressedKeyArr[A] || m_pressedKeyArr[D] || m_pressedKeyArr[S] \
	|| m_pressedKeyArr[UPARR] || m_pressedKeyArr[LEFTARR] || m_pressedKeyArr[RIGHTARR] || m_pressedKeyArr[DOWNARR]))
		m_playerHasMoved = true;

	if (m_playerHasMoved == true)
		m_player.movePlayer(dt, m_gravityVelocity, m_gravityDir);

	checkCollisions();

	if (!m_firstGravityChange)
		m_info.update(GRAVITY_RECHARGE);
	else
		m_info.update(m_gravityClock.getElapsedTime().asSeconds());
}

void	GameHandler::handleSidewaysMovement()
{
	if (m_gravityDir == DOWN || m_gravityDir == UP)
	{
		if (m_pressedKeyArr[A])
			m_player.getDirVec().x = -1;
		else if (m_pressedKeyArr[D])
			m_player.getDirVec().x = 1;
		else if (!m_pressedKeyArr[A] && !m_pressedKeyArr[D])
			m_player.getDirVec().x = 0;
	}
	else
	{
		if (m_pressedKeyArr[W])
			m_player.getDirVec().y = -1;
		else if (m_pressedKeyArr[S])
			m_player.getDirVec().y = 1;
		else if (!m_pressedKeyArr[W] && !m_pressedKeyArr[S])
			m_player.getDirVec().y = 0;
	}
}

/*
	DRAW
*/

void	GameHandler::drawStartScreen(sf::RenderWindow &window, float dt)
{
	m_startscreen.drawScreen(window, dt);
}

void	GameHandler::drawEndScreen(sf::RenderWindow &window)
{
	if (m_end.getScoreString().empty())
		m_end.setScoreString(m_info.getScore());

	m_end.draw(window);
}

void	GameHandler::drawGame(sf::RenderWindow &window)
{
	if (m_gameState == END)
		return ;

	m_map.drawMap(window);
	window.draw(m_player.getSprite());
	m_collectible.drawCollectible(window);
	m_info.drawInfoScreen(window);
}

/*
	SETTERS
*/

void	GameHandler::setKeypressState(bool state, int key)
{
	m_pressedKeyArr[key] = state;
}

void	GameHandler::setGameState(int newState)
{
	m_gameState = newState;
}

/*
	GETTERS
*/

Player	&GameHandler::getPlayer()
{
	return (m_player);
}

Map		&GameHandler::getMap()
{
	return (m_map);
}

Collectible &GameHandler::getCollectible()
{
	return (m_collectible);
}

InfoScreen	&GameHandler::getInfoScreen()
{
	return (m_info);
}

int		GameHandler::getGameState()
{
	return (m_gameState);
}

