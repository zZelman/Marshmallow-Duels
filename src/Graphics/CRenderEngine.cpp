/*
 * CRenderEngine.cpp
 *
 *  Created on: Jan 1, 2014
 *      Author: zZelman
 */

#include "../Headers/CRenderEngine.h"
#include "../Headers/include_sfml.h"
#include <sstream>

CRenderEngine::CRenderEngine(sf::RenderWindow* pWindow,
                             CTile_Container* pTile_Container,
                             CPlayer* pPlayer)
{
	m_pWindow 			= pWindow;
	m_pTile_Container 	= pTile_Container;
	m_pPlayer 			= pPlayer;

	m_pSprite = NULL;

	sf::Vector2u window_size = m_pWindow->getSize();
	m_view.reset(sf::FloatRect(0, 0, window_size.x, window_size.y));
	m_view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
}


CRenderEngine::~CRenderEngine()
{
}


void CRenderEngine::render()
{
	// fill lists with respective data
	getData();

	// * render each type in a specific order
	// * remember: law of super-position - things rendered
	//		later will be on top
	// * each individually determines whether or not the object
	//		can be seen by calling canBeSeen(...);
	render_obj(&m_tiles);
	render_obj(&m_players);
	render_UI();
	render_HUD();
	render_menu();
}


void CRenderEngine::getData()
{
	m_players.clear();
	m_players.push_back(m_pPlayer);

	m_tiles.clear();
	m_pTile_Container->getRenderData(&m_tiles);
}


bool CRenderEngine::canBeSeen(ARenderable* pRender)
{
	// retrieve data
	m_view = m_pWindow->getView();

	m_viewTopLeft.x = m_view.getCenter().x - (m_view.getSize().x) / 2;
	m_viewTopLeft.y = m_view.getCenter().y - (m_view.getSize().y) / 2;

	m_viewSize = m_view.getSize();

	m_screenRect.left 	= m_viewTopLeft.x;
	m_screenRect.top 	= m_viewTopLeft.y;
	m_screenRect.width	= m_viewSize.x;
	m_screenRect.height	= m_viewSize.y;

	// test to see if the object is within the current window view
	if (pRender->getGlobalBounds().intersects(m_screenRect) == true)
	{
		return true;
	}

	// object cannot be seen
	return false;
}


void CRenderEngine::render_obj(std::list<ARenderable*>* pList)
{
	for (std::list<ARenderable*>::iterator itr = pList->begin();
	        itr != pList->end();
	        ++itr)
	{
		if (canBeSeen(*itr))
		{
			m_pSprite = (*itr)->getSprite_API();
			m_pWindow->draw(*m_pSprite);
		}
	}
}


void CRenderEngine::render_UI()
{
}


void CRenderEngine::render_HUD()
{
}


void CRenderEngine::render_menu()
{
}
