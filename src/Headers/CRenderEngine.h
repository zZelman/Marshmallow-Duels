/*
 * CRenderEngine.h
 *
 *  Created on: Jan 1, 2014
 *      Author: zZelman
 */

#ifndef CRENDERENGINE_H_
#define CRENDERENGINE_H_

#include "include_sfml.h"
#include "ARenderable.h"
#include "CTile_Container.h"
#include "CPlayer.h"

#include <list>


/**
 * Module of the game engine that is responsible for rendering all ARenderable
 * game objects in an ordered fashion.
 *
 * @see ARenderable
 */
class CRenderEngine
{
public:
	CRenderEngine(sf::RenderWindow* pWindow,
	              CTile_Container* pTile_Container,
	              CPlayer* pPlayer);
	~CRenderEngine();

	/**
	 * Renders each ARenderable game object, and renders in reverse order (bottom first)
	 * because of super-position.
	 *
	 * Priority in rendering: ([top] Menu, HUD, UI, Players, Tiles [bottom])
	 */
	void render();

private:
	/**
	 * Pointer to the API window.
	 *
	 * Note: CRenderEngine does not take responsibility for it
	 */
	sf::RenderWindow* m_pWindow;

	/**
	 * TEMPORARY.
	 *
	 * This will only exist as long as the simple example does
	 */
	CPlayer* m_pPlayer;

	/**
	 * Temporary container for all players in existence.
	 *
	 * Temporary in the sense that the contents is filled and cleared
	 * EACH render call
	 */
	std::list<ARenderable*> m_players;

	/**
	 * Pointer to the tile container to withdraw the individual tiles
	 */
	CTile_Container* m_pTile_Container;

	/**
	 * list which is cleared, then re-filled before each render call is satisfied
	 * with the individual tiles within the tile container
	 */
	std::list<ARenderable*> m_tiles;

	/**
	 * Current sprite being rendered.
	 *
	 * Allocated here because it is used in all render functions,
	 * increases efficacy.
	 */
	sf::Sprite* m_pSprite;


	/**
	 * Data fields used by canBeSeen().
	 *
	 * Allocated here to increase efficacy.
	 *
	 * @see canBeSeen()
	 */
	sf::View m_view;
	sf::Vector2f m_viewSize;
	sf::Vector2f m_viewTopLeft;
	sf::FloatRect m_screenRect;

	/**
	 * Fills the temporary containers.
	 *
	 * @see m_players
	 * @see m_tiles
	 */
	void getData();

	/**
	 * Determines whether or not the thing is within the window subsection of the
	 * overall world (able to be seen).
	 *
	 * @return true = can be seen; false = can't be seen and therefore don't render
	 */
	bool canBeSeen(ARenderable* pRender);

	/**
	 * Renders a list of ARenderable pointers
	 *
	 * @see ARenderable
	 */
	void render_obj(std::list<ARenderable*>* pList);

	/**
	 * Renders the UI
	 */
	void render_UI();

	/**
	 * Renders the Heads Up Display
	 */
	void render_HUD();

	/**
	 * Renders the menu (if it is open)
	 */
	void render_menu();

};

#endif /* CRENDERENGINE_H_ */
