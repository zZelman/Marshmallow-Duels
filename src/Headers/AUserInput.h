/*
 * IUserInput.h
 *
 *  Created on: Oct 19, 2013
 *      Author: zZelman
 */

#ifndef AUSERINPUT_H_
#define AUSERINPUT_H_

#include "include_sfml.h"

/**
 * Abstract class which decomposes the different types of user input.
 */
class AUserInput
{
public:
	AUserInput();
	virtual ~AUserInput();

	// "pressed" or "released" is determined by the overarching game structure
	virtual bool userInput_keyPress(sf::Event* pEvent) = 0;
	virtual bool userInput_keyRelease(sf::Event* pEvent) = 0;

	virtual bool userInput_mousePress(sf::Event* pEvent) = 0;
	virtual bool userInput_mouseRelease(sf::Event* pEvent) = 0;

protected:
	/**
	 * Representation of acceptable key presses, and states of those keys
	 */
	struct SKeyStates
	{
		/**
		 *  Acceptable keys
		 */
		sf::Keyboard::Key up, down, left, right;

		/**
		 * States of the acceptable keys
		 */
		bool isUp, isDown, isLeft, isRight;

		/**
		 * Sets all states to null
		 */
		void nullStates();
	} m_sKeys;

	// TODO: does the deriving classes need a common "set_keybinds" function?
};

#endif /* IUSERINPUT_H_ */
