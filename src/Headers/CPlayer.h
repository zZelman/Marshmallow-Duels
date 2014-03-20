/*
 * CPlayer.h
 *
 *  Created on: Feb 14, 2014
 *      Author: zZelman
 */

#ifndef CPLAYER_H_
#define CPLAYER_H_

#include "include_sfml.h"
#include "ARenderable.h"
#include "AUpdate.h"
#include "AUserInput.h"
#include "CTexture.h"
#include "DPhysics.h"

/**
 * Base class of each individual player.
 *
 * The player is the thing that the human person controls in the game world
 */
class CPlayer: public ARenderable, public AUpdate, public AUserInput, public DPhysics
{
public:
	CPlayer(CTexture* pTexture,
	        const sf::Vector2<int>& currSub);
	~CPlayer();

	/**
	 * Function to update object state each update cycle
	 */
	void update();

	bool userInput_keyPress(sf::Event* pEvent);
	bool userInput_keyRelease(sf::Event* pEvent);

	bool userInput_mousePress(sf::Event* pEvent);
	bool userInput_mouseRelease(sf::Event* pEvent);

	void stepNormally();

private:
	/**
	 * linear movement step while a move key is down.
	 */
	int moveStep;

	/**
	 * Current bounds of the sprite.
	 *
	 * Allocated here to increase efficacy
	 */
	sf::FloatRect currentBounds;

	/**
	 * Convenience function to set the key states for up,down,left,right and
	 * null their states at the start of execution
	 */
	void setKeybinds();

	/**
	 * Updates the view variable so that the render engine knows what to render
	 * for this specific player.
	 *
	 * @see m_view
	 */
	void update_view();

	/**
	 * Wrapper function to the move_* functions.
	 *
	 * @see move_up()
	 * @see move_down()
	 * @see move_left()
	 * @see move_right()
	 */
	void update_position();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
};

#endif /* CPLAYER_H_ */
