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

/**
 * Module of the game engine that is responsible for: resolving collisions and
 * updating physics data within objects.
 */
class CPhysicsEngine : public IUpdateable
{
public:
	CPhysicsEngine(CPlayer* pPlayer,
	               CTile_Container* pTile_Container);
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
	 * @return true if collision
	 */
	bool player_tile(CPlayer* pPlayer, CTile* pTile);


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
