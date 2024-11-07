#ifndef GAMEHANDLER_HPP
# define GAMEHANDLER_HPP

# include <iostream>

# include "Constants.hpp"
# include "Collectible.hpp"
# include "Player.hpp"
# include "Map.hpp"
# include "InfoScreen.hpp"
# include "StartScreen.hpp"
# include "EndScreen.hpp"

class GameHandler
{
	private:

	Player		m_player;
	Map			m_map;
	Collectible	m_collectible;
	InfoScreen	m_info;
	StartScreen	m_startscreen;
	EndScreen	m_end;
	sf::Clock	m_gravityClock;

	int		m_gameState;
	float	m_gravityVelocity;
	int		m_gravityDir;
	bool	m_pressedKeyArr[8];
	bool	m_collisionFlagArr[4];
	bool	m_firstGravityChange;
	bool	m_playerHasMoved;

	void	handleSidewaysMovement();

	// Collision handling implementations can be found in the 'collisionHandling.cpp' -file
	void	checkCollisions();
	void	checkWallCollision();
	void	getCollisionFlag(mapTile &tile);

/////

	public:

	GameHandler();
	~GameHandler() {};

	void	initGame();
	void	checkInput(sf::Event &event);
	void	checkRelease(sf::Event &event);
	void	drawStartScreen(sf::RenderWindow &window, float dt);
	void	drawEndScreen(sf::RenderWindow &window);
	void	updateGame(float dt);
	void	drawGame(sf::RenderWindow &window);

	void		setKeypressState(bool state, int direction);
	void		setGameState(int newState);
	Player		&getPlayer();
	Map			&getMap();
	Collectible &getCollectible();
	InfoScreen	&getInfoScreen();
	int			getGameState();
};

#endif