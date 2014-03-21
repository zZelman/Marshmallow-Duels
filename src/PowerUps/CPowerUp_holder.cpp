#include "../Headers/CPowerUp_holder.h"

CPowerUp_holder::CPowerUp_holder(CTexture* pTexture, const sf::Vector2<int>& currSub,
                                 const sf::Vector2<int>& spawnPos, const sf::Vector2<int>& spawnSpeeds)
	: ARenderable(pTexture, currSub), AUpdate(), DPhysics()
{
	m_pSprite->setPosition(spawnPos.x, spawnPos.y);
	m_sPhysics.velosity_x = spawnSpeeds.x;
	m_sPhysics.velosity_y = spawnSpeeds.y;
}


CPowerUp_holder::~CPowerUp_holder()
{
}


void CPowerUp_holder::update()
{
	if (m_isFirstUpdate)
	{
		m_sPhysics.gravityTimer.restart();

		m_isFirstUpdate = false;
		return;
	}
}


void CPowerUp_holder::stepNormally()
{
	// vertical
	int stepSize_y = m_sPhysics.velosity_y;

	// horizontal
	int stepSize_x = m_sPhysics.velosity_x;

	m_pSprite->move(stepSize_x, stepSize_y);
}
