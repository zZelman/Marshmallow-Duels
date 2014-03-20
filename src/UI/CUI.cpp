/*
 * CUI.cpp
 *
 *  Created on: Jan 2, 2014
 *      Author: zZelman
 */

#include "../Headers/CUI.h"

#include <iostream>

CUI::CUI(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}


CUI::~CUI()
{
}


void CUI::update()
{
}


bool CUI::userInput_keyPress(sf::Event* pEvent)
{
	if (m_pPlayer->userInput_keyPress(pEvent))
	{
		return true;
	}

	// UI not consumed by any module
	return false;
}


bool CUI::userInput_keyRelease(sf::Event* pEvent)
{
	if (m_pPlayer->userInput_keyRelease(pEvent))
	{
		return true;
	}


	// UI not consumed by any module
	return false;
}


bool CUI::userInput_mousePress(sf::Event* pEvent)
{
	if (pEvent->mouseButton.button == sf::Mouse::Left)
	{
	}
	else if (pEvent->mouseButton.button == sf::Mouse::Right)
	{
	}

	// UI not consumed by any module
	return false;
}


bool CUI::userInput_mouseRelease(sf::Event* pEvent)
{
	if (pEvent->mouseButton.button == sf::Mouse::Left)
	{
	}
	else if (pEvent->mouseButton.button == sf::Mouse::Right)
	{
	}

	// UI not consumed by any module
	return false;
}
