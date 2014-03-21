/*
 * DPhysics.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#include "../Headers/DPhysics.h"


DPhysics::DPhysics()
{
	moveStep = 0;
	m_sPhysics.nullAll();
}


DPhysics::~DPhysics()
{
}


void DPhysics::SPhysics::nullAll()
{
	gravityTimer.restart();

	velosity_x = 0;
	velosity_y = 0;

	isFalling = false;
	isJumping = false;

	isCollision_h = false;
}
