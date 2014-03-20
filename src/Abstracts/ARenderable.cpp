/*
 * IRenderable.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: zZelman
 */

#include "../Headers/ARenderable.h"
#include "../Headers/CSprite.h"

ARenderable::ARenderable(CTexture* pTexture,
                         const sf::Vector2<int>& currSub)
{
	m_pSprite = new CSprite(pTexture, currSub);
	hasView = false;
}


ARenderable::ARenderable(CSprite* pSprite)
{
	m_pSprite = pSprite;
}


ARenderable::~ARenderable()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


CSprite* const ARenderable::getSprite() const
{
	return m_pSprite;
}


sf::Sprite* const ARenderable::getSprite_API() const
{
	return m_pSprite;
}


sf::FloatRect ARenderable::getGlobalBounds()
{
	return m_pSprite->getGlobalBounds();
}


const sf::View& ARenderable::getView() const
{
	return m_view;
}

bool ARenderable::getHasView() const
{
	return hasView;
}


void ARenderable::setPosition(float x, float y)
{
	m_pSprite->setPosition(x, y);
}
