/*
 * CPlayer.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: zZelman
 */

#include "../Headers/CPlayer.h"
#include <iostream>

CPlayer::CPlayer(CTexture* pTexture, const sf::Vector2<int>& currSub)
	: ARenderable(pTexture, currSub), AUpdate(), AUserInput(), DPhysics()
{
	moveStep = 3;

	setKeybinds();

	m_sPhysics.isFalling = true;

	hasView = true;
	update_view();
}


CPlayer::~CPlayer()
{
}


void CPlayer::setKeybinds()
{
	m_sKeys.nullStates();

	m_sKeys.up 		= sf::Keyboard::W;
	m_sKeys.down 	= sf::Keyboard::S;
	m_sKeys.left 	= sf::Keyboard::A;
	m_sKeys.right 	= sf::Keyboard::D;
}


bool CPlayer::userInput_keyPress(sf::Event* pEvent)
{
	// up
	if (pEvent->key.code == m_sKeys.up)
	{
		m_sKeys.isUp = true;

		return true;
	}

	// down
	if (pEvent->key.code == m_sKeys.down)
	{
		m_sKeys.isDown = true;

		return true;
	}

	// left
	if (pEvent->key.code == m_sKeys.left)
	{
		m_sKeys.isLeft = true;
		m_sPhysics.velosity_x = -moveStep;

		return true;
	}

	// right
	if (pEvent->key.code == m_sKeys.right)
	{
		m_sKeys.isRight = true;
		m_sPhysics.velosity_x = moveStep;

		return true;
	}


	// UI not consumed
	return false;
}


bool CPlayer::userInput_keyRelease(sf::Event* pEvent)
{
	// up
	if (pEvent->key.code == m_sKeys.up)
	{
		m_sKeys.isUp = false;

		return true;
	}

	// down
	if (pEvent->key.code == m_sKeys.down)
	{
		m_sKeys.isDown = false;

		return true;
	}

	// left
	if (pEvent->key.code == m_sKeys.left)
	{
		m_sKeys.isLeft = false;
		m_sPhysics.velosity_x = 0;

		return true;
	}

	// right
	if (pEvent->key.code == m_sKeys.right)
	{
		m_sKeys.isRight = false;
		m_sPhysics.velosity_x = 0;

		return true;
	}

	// UI not consumed
	return false;
}


bool CPlayer::userInput_mousePress(sf::Event* pEvent)
{
	return false;
}


bool CPlayer::userInput_mouseRelease(sf::Event* pEvent)
{
	return false;
}


void CPlayer::stepNormally()
{
	// vertical
	int stepSize_y = m_sPhysics.velosity_y;

	// horizontal
	int stepSize_x = m_sPhysics.velosity_x;

	m_pSprite->move(stepSize_x, stepSize_y);
}


void CPlayer::update()
{
	if (m_isFirstUpdate)
	{
		m_sPhysics.gravityTimer.restart();

		m_isFirstUpdate = false;
		return;
	}

	update_view();

	update_position();
}


void CPlayer::update_view()
{
	int viewDist = 15;
	float sizeW = 32 * viewDist;
	float sizeH = 32 * viewDist;

	sf::FloatRect currRect = m_pSprite->getGlobalBounds();
	float centerX = currRect.left + (currRect.width / 2);
	float centerY = currRect.top + (currRect.height / 2);

	m_view.setSize(sizeW, sizeH);
	m_view.setCenter(centerX, centerY);
}


void CPlayer::update_position()
{
	if (m_sKeys.isUp && !m_sKeys.isDown)
	{
		move_up();
	}

	if (m_sKeys.isDown && !m_sKeys.isUp)
	{
		move_down();
	}

	if (m_sKeys.isLeft && !m_sKeys.isRight)
	{
		move_left();
	}

	if (m_sKeys.isRight && !m_sKeys.isLeft)
	{
		move_right();
	}
}


void CPlayer::move_up()
{
	m_sPhysics.isJumping = true;
	m_sPhysics.isFalling = false;

	m_sPhysics.gravityTimer.restart();

	m_pSprite->setSubImage(1, 1);
}


void CPlayer::move_down()
{
	m_pSprite->setSubImage(2, 1);
}


void CPlayer::move_left()
{
	m_pSprite->setSubImage(1, 2);
}


void CPlayer::move_right()
{
	m_pSprite->setSubImage(2, 2);
}
