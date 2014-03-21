/*
 * CGame.h
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#ifndef CGAME_H_
#define CGAME_H_

#include "Headers/include_sfml.h"

#include "Headers/CRenderEngine.h"
#include "Headers/include_graphics.h"

#include "Headers/CUI.h"

#include "Headers/CTile_Container.h"

#include "Headers/CPhysicsEngine.h"

#include "Headers/CPowerUp_Container.h"

/**
 * Host of game-loop and program flow therein, also handles SFML "system" events.
 */
class CGame
{
public:
	CGame();
	~CGame();

	sf::RenderWindow* getGameWindow();

	bool getIsRunning();
	bool getIsPaused();

	void startGame();
	void stopGame();

private:
	sf::RenderWindow* m_pWindow;

	CPhysicsEngine* m_pPhysicsEngine;
	CRenderEngine* m_pRenderEngine;
	CPowerUp_Container* m_pPowerUp_Container;
	CUI* m_pUI;

	/**
	 * TEMPORARY.
	 *
	 * This will only exist as long as the simple example does
	 */
	CPlayer* m_pPlayer;

	/**
	 * TEMPORARY.
	 *
	 * This will only exist as long as the simple example does
	 */
	CTexture* m_pTexture_player;

	/**
	 * Container of each individual tile in the world
	 */
	CTile_Container* m_pTile_Container;

	bool isRunning;
	bool isPaused;

	/**
	 * Creates the window and sets settings for the window.
	 */
	void initWindow();

	/**
	 * Main game loop of the program.
	 *
	 * Calls input_*, then update, then render in succession
	 *
	 * @see input_gameSystem
	 * @see input_user
	 * @see update
	 * @see render
	 */
	void gameLoop();

	/**
	 * Manages 'system' events such as window focus, window dimension changes, etc.
	 */
	bool input_gameSystem(sf::Event* pEvent);

	/**
	 * Manages user (human player) input events, such as key presses and mouse presses
	 */
	bool input_user(sf::Event* pEvent);

	/**
	 * Updates game object(s) states/data
	 */
	void update();

	/**
	 * Renders game object(s) based on their states/data.
	 *
	 * Treats each object as static data; does not do any modifications.
	 */
	void render();
};

#endif /* CGAME_H_ */
