/*
 * CPhysicsEngine.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#include "../Headers/CPhysicsEngine.h"
#include <iostream>

CPhysicsEngine::CPhysicsEngine(CPlayer* pPlayer,
                               CTile_Container* pTile_Container)
{
	m_pTile_Container = pTile_Container;

	m_pPlayer = pPlayer;

}


CPhysicsEngine::~CPhysicsEngine()
{
}


void CPhysicsEngine::update()
{
	n2_collision();
}


void CPhysicsEngine::n2_collision()
{
	// DEBUG printing the movement state of the object(s)
//	std::cout << "fall: " << m_pPlayer->m_sPhysics.isFalling << std::endl
//	          << "jump: " << m_pPlayer->m_sPhysics.isJumping << std::endl << std::endl;

	std::list<ARenderable*> tiles;
	m_pTile_Container->getCollisiondata(&tiles);

	std::list<ARenderable*> players;
	players.push_back(m_pPlayer);

	CTile* pTile = NULL;
	CPlayer* pPlayer = NULL;
	bool canStepNormally = true;
	std::list<DPhysics*> normals; // objects that can step normally


	for (std::list<ARenderable*>::iterator itr_players = players.begin();
	        itr_players != players.end();
	        ++itr_players)
	{
		canStepNormally = true;

		pPlayer = dynamic_cast<CPlayer*>(*itr_players);
		applyPhysics(pPlayer);

		for (std::list<ARenderable*>::iterator itr_tiles = tiles.begin();
		        itr_tiles != tiles.end();
		        ++itr_tiles)
		{
			pTile = dynamic_cast<CTile*>(*itr_tiles);

			if (player_tile(pPlayer, pTile) == true)
			{
				canStepNormally = false;
				break;
			}
		}

		if (canStepNormally == true)
		{
			normals.push_front(pPlayer);

			if (pPlayer->m_sPhysics.isJumping == false)
			{
				pPlayer->m_sPhysics.isFalling = true;
			}
		}

	}

	applyStepNormally(&normals);
}


bool CPhysicsEngine::player_tile(CPlayer* pPlayer, CTile* pTile)
{
	bool isCollision = false;

	sf::FloatRect currRect 		= pPlayer->getGlobalBounds();
	sf::FloatRect futureRect_v 	= pPlayer->getGlobalBounds(); // vertical future
	sf::FloatRect futureRect_h 	= pPlayer->getGlobalBounds(); // horizontal future
	sf::FloatRect tileRect 		= pTile->getGlobalBounds();

	int newY = currRect.top;
	int newX = currRect.left;

	DPhysics::SPhysics& physicsData = pPlayer->m_sPhysics;

	int& velY = physicsData.velosity_y;
	int& velX = physicsData.velosity_x;

	futureRect_v.top  += velY;
	futureRect_h.left += velX;


	// VERTICAL
	if (futureRect_v.intersects(tileRect) &&
	        (velY != 0))
	{
		// DEBUG printing
//		using namespace std;
//		cout << "coll type : vertical" << endl;
//		cout << "move type : (j: " << physicsData.isJumping << ") ; (f: " << physicsData.isFalling << ")" << endl;
//		cout << "vel stats : " << velY << endl;


		if (velY > 0) // down
		{
			newY = tileRect.top - currRect.height;

			physicsData.isFalling = false;
			physicsData.isJumping = false;
		}
		else if (velY < 0) // up
		{
			newY = tileRect.top + tileRect.height;

			physicsData.isFalling = true;
			physicsData.isJumping = false;
		}

		physicsData.gravityTimer.restart();
		velY = 0;

		isCollision = true;

		pPlayer->setPosition(newX, newY);


		// DEBUG printing
//		cout << "tile cords: (" << tileRect.left << ", " << tileRect.top << ")" << endl;
//		cout << "new player: (" << newX << ", " << newY << ")" << endl;
//		cout << endl;
	}


	// HORIZONTAL
	if (futureRect_h.intersects(tileRect) &&
	        (velX != 0))
	{
		// DEBUG printing
//		using namespace std;
//		cout << "coll type : horizontal" << endl;
//		cout << "vel stats : " << velX << endl;


		if (velX > 0) // right
		{
			newX = tileRect.left - currRect.width;
		}
		else if (velX < 0) // left
		{
			newX = tileRect.left + tileRect.width;
		}

		velX = 0;

		pPlayer->setPosition(newX, newY);

		isCollision = true;

		physicsData.isCollision_h = true;

		// DEBUG printing
//		cout << "tile cords: (" << tileRect.left << ", " << tileRect.top << ")" << endl;
//		cout << "new player: (" << newX << ", " << newY << ")" << endl;
//		cout << endl;
	}
	else
	{
		physicsData.isCollision_h = false;
	}


	return isCollision;
}


void CPhysicsEngine::applyPhysics(DPhysics* pObject)
{
	sf::Time timer = pObject->m_sPhysics.gravityTimer.getElapsedTime();

	double elapsed = timer.asMilliseconds();

	// make game look nice
	// remember 'elapsed' is in MS, this reduces that massive x var
	double reductionFactor = 0.005;

	bool isJumping = pObject->m_sPhysics.isJumping;
	bool isFalling = pObject->m_sPhysics.isFalling;

	if (isJumping)
	{
		pObject->m_sPhysics.velosity_y = 3.0f * (reductionFactor * elapsed) - 5;
	}

	if (isFalling)
	{
		pObject->m_sPhysics.velosity_y = 3.0f * (reductionFactor * elapsed);
	}
}


void CPhysicsEngine::applyStepNormally(std::list<DPhysics*>* pList)
{
	for (std::list<DPhysics*>::iterator itr = pList->begin();
	        itr != pList->end();
	        ++itr)
	{
		(*itr)->stepNormally();
	}
}
