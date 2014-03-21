/*
 * CPhysicsEngine.h
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#ifndef CPHYSICSENGINE_H_
#define CPHYSICSENGINE_H_

#include "CTile_Container.h"
#include "CPlayer.h"

#include "IUpdateable.h"
#include "DPhysics.h"
#include "CPowerUp_holder.h"

/**
 * Module of the game engine that is responsible for: resolving collisions and
 * updating physics data within objects.
 */
class CPhysicsEngine : public IUpdateable
{
public:
	CPhysicsEngine(CPlayer* pPlayer,
	               CPowerUp_holder* pPowerUp_holder,
	               CTile_Container* pTile_Container,
	               sf::RenderWindow* pWindow);
	~CPhysicsEngine();


	/**
	 * Only updates the velocities within the objects, and calls "stepNormally()" if it
	 * can step normally within the next update
	 *
	 * Does not call the object's "update()" function!!
	 */
	void update();

private:
	// pointer to the object maintainers
	CTile_Container* m_pTile_Container;

	CPlayer* m_pPlayer;

	CPowerUp_holder* m_pPowerUp_holder;

	sf::RenderWindow* m_pWindow;

	/**
	 * fast and easy O(n^2) collision detection
	 */
	void n2_collision();

	/**
	 * A potential collision has been found between these two given pointers by
	 * the calling function, it is resolved here.
	 *
	 * Naming scheme is "this collides with that" (player -> tile == player_tile)
	 *
	 * @return true if collision && therefore resolution
	 */
	bool player_tile(CPlayer* pPlayer, CTile* pTile);

	/**
	 * A potential collision has been found between these two given pointers by
	 * the calling function, it is resolved here.
	 *
	 * Naming scheme is "this collides with that" (player -> tile == player_tile)
	 *
	 * @return true if collision
	 */
	bool player_powerUpHolder(CPlayer* pPlayer, CPowerUp_holder* pHolder);

	/**
	 * The behavior of holders is simply to bounce off of the window edges.
	 *
	 * @return true if rebound has occurred.
	 */
	bool powerUpHolder_window(CPowerUp_holder* pHolder);


	/**
	 * Applies physics to the vertical movement of the given object.
	 *
	 * Contains the mathematical expression to determine the velocity
	 */
	void applyPhysics(DPhysics* pObject);

	/**
	 * calls update normally on all in the list
	 *
	 * it has been determined externally whether or not the objects within the list
	 * can step normally, and it is assumed that they can
	 */
	void applyStepNormally(std::list<DPhysics*>* pList);
};

#endif /* CPHYSICSENGINE_H_ */
