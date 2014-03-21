/*
 * CPhysicsEngine.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#include "../Headers/CPhysicsEngine.h"
#include <iostream>

CPhysicsEngine::CPhysicsEngine(CPlayer* pPlayer,
                               CPowerUp_Container* pPowerUp_Container,
                               CTile_Container* pTile_Container,
                               sf::RenderWindow* pWindow)
{
	m_pTile_Container = pTile_Container;

	m_pPlayer = pPlayer;

	m_pPowerUp_Container = pPowerUp_Container;

	m_pWindow = pWindow;

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
	m_pTile_Container->getCollisionData(&tiles);

	std::list<ARenderable*> players;
	players.push_back(m_pPlayer);

	std::list<ARenderable*> powerUps;
	m_pPowerUp_Container->getCollisionData(&powerUps);

	CTile* pTile = NULL;
	CPlayer* pPlayer = NULL;
	CPowerUp_holder* pPowerUp_holder = NULL;
	bool canStepNormally_player = true;
	std::list<DPhysics*> normals; // objects that can step normally


	// POWERUP_HOLDER -> WINDOW EDGE
	for (std::list<ARenderable*>::iterator itr_powerUp_holder = powerUps.begin();
	        itr_powerUp_holder != powerUps.end();
	        ++itr_powerUp_holder)
	{
		pPowerUp_holder = dynamic_cast<CPowerUp_holder*>(*itr_powerUp_holder);

		if (powerUpHolder_window(pPowerUp_holder) == true)
		{
			std::cout << "powerUpHolder_window" << std::endl;
		}
		else
		{
			normals.push_front(pPowerUp_holder);
		}
	}


	// PLAYER -> *
	for (std::list<ARenderable*>::iterator itr_players = players.begin();
	        itr_players != players.end();
	        ++itr_players)
	{
		canStepNormally_player = true;

		pPlayer = dynamic_cast<CPlayer*>(*itr_players);
		applyPhysics(pPlayer);

		// PLAYER -> TILE
		for (std::list<ARenderable*>::iterator itr_tiles = tiles.begin();
		        itr_tiles != tiles.end();
		        ++itr_tiles)
		{
			pTile = dynamic_cast<CTile*>(*itr_tiles);

			if (player_tile(pPlayer, pTile) == true)
			{
				canStepNormally_player = false;
				break;
			}
		}

		// PLAYER -> POWERUP_HOLDER
		for (std::list<ARenderable*>::iterator itr_powerUp_holder = powerUps.begin();
		        itr_powerUp_holder != powerUps.end();
		        ++itr_powerUp_holder)
		{
			pPowerUp_holder = dynamic_cast<CPowerUp_holder*>(*itr_powerUp_holder);

			if (player_powerUpHolder(pPlayer, pPowerUp_holder) == true)
			{
				std::cout << "player_powerUpHolder" << std::endl;
			}
		}

		if (canStepNormally_player == true)
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


bool CPhysicsEngine::player_powerUpHolder(CPlayer* pPlayer,
        CPowerUp_holder* pHolder)
{
	sf::FloatRect playerR = pPlayer->getGlobalBounds();
	sf::FloatRect holderR = pHolder->getGlobalBounds();

	if (holderR.intersects(playerR))
	{
		return true;
	}

	return false;
}


bool CPhysicsEngine::powerUpHolder_window(CPowerUp_holder* pHolder)
{
	sf::FloatRect currRect 		= pHolder->getGlobalBounds();
	sf::FloatRect futureRect_v 	= pHolder->getGlobalBounds(); // vertical future
	sf::FloatRect futureRect_h 	= pHolder->getGlobalBounds(); // horizontal future
	sf::Vector2u windowSize = m_pWindow->getSize();

	int newY = currRect.top;
	int newX = currRect.left;

	DPhysics::SPhysics& physicsData = pHolder->m_sPhysics;

	int& velY = physicsData.velosity_y;
	int& velX = physicsData.velosity_x;

	futureRect_v.top  += velY;
	futureRect_h.left += velX;

	bool isCollision = false;

	// left side of window
	if (futureRect_h.left < 0)
	{
		newX = 0;
		velX = -velX;
		isCollision = true;
	}
	// right side of window
	else if ((futureRect_h.left + currRect.width) > windowSize.x)
	{
		newX = windowSize.x - currRect.width;
		velX = -velX;
		isCollision = true;
	}

	// top of window
	if (futureRect_v.top < 0)
	{
		newY = 0;
		velY = -velY;
		isCollision = true;
	}
	else if ((futureRect_v.top + currRect.height) > windowSize.y)
	{
		newY = windowSize.y - currRect.height;
		velY = -velY;
		isCollision = true;
	}

	if (isCollision)
	{
		pHolder->setPosition(newX, newY);
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
