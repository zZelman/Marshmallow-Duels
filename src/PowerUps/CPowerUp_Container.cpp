#include "../Headers/CPowerUp_Container.h"

CPowerUp_Container::CPowerUp_Container()
{
	m_pTexture_powerUpHolder = new CTexture("res/Power Ups/debug_holder (20x20, 1x1).png",
	                                        sf::Vector2<int>(20, 20),
	                                        sf::Vector2<int>(1, 1));
	m_pPowerUp_holder = new CPowerUp_holder(m_pTexture_powerUpHolder,
	                                        sf::Vector2<int>(1, 1),
	                                        sf::Vector2<int>(20, 20),
	                                        sf::Vector2<int>(4, 5));
	m_holder_active.push_back(m_pPowerUp_holder);
}

CPowerUp_Container::~CPowerUp_Container()
{
	delete m_pTexture_powerUpHolder;
	m_pTexture_powerUpHolder = NULL;

	delete m_pPowerUp_holder;
	m_pPowerUp_holder = NULL;
}

void CPowerUp_Container::update()
{
	for (std::list<CPowerUp_holder*>::iterator itr = m_holder_active.begin();
	        itr != m_holder_active.end();
	        ++itr)
	{
		(*itr)->update();
	}
}

void CPowerUp_Container::getRenderData(std::list<ARenderable*>* pList)
{
	for (std::list<CPowerUp_holder*>::iterator itr = m_holder_active.begin();
	        itr != m_holder_active.end();
	        ++itr)
	{
		pList->push_front((*itr));
	}
}

void CPowerUp_Container::getCollisionData(std::list<ARenderable*>* pList)
{
	for (std::list<CPowerUp_holder*>::iterator itr = m_holder_active.begin();
	        itr != m_holder_active.end();
	        ++itr)
	{
		pList->push_front((*itr));
	}
}
