/*
 * DPhysics.h
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#ifndef DPHYSICS_H_
#define DPHYSICS_H_

#include "include_sfml.h"

/**
 * Base class holder of pertinent physics information within a
 * SPhysics
 */
class DPhysics
{
public:
	DPhysics();
	virtual ~DPhysics();

	/**
	 * Physics data
	 */
	struct SPhysics
	{
		/**
		 * Time since last stand still.
		 *
		 * Used in parabolic curve mapping.
		 */
		sf::Clock gravityTimer;
		int velosity_x; /**< Velocity on the x axis. Positive is moving right */
		int velosity_y; /**< Velocity on the y axis. Positive is moving down */

		bool isFalling; /**< Object passively fell off of something */
		bool isJumping; /**< Object actively choose to jump */

		/**
		 * Sets all data values within m_sPhysics to NULL, and restarts gravityTimer.
		 */
		void nullAll();
	} m_sPhysics;

	/**
	 * A normal step in 1 update call.
	 *
	 * When this method is called, it is assumed that there will NOT
	 * be a collision during 1 step.
	 */
	virtual void stepNormally() = 0;
};

#endif /* DPHYSICS_H_ */
