#ifndef CPOWERUP_CONTAINER_H_
#define CPOWERUP_CONTAINER_H_

#include "IUpdateable.h"
#include "IGetRenderData.h"
#include "IGetCollisionData.h"
#include "CPowerUp_holder.h"

#include <list>

/**
 * Container for all Power Ups; Active, Holders, and Passive.
 */
class CPowerUp_Container: public IUpdateable,
	public IGetRenderData,
	public IGetCollisionData
{
public:
	CPowerUp_Container();
	~CPowerUp_Container();

	void update();

	void getRenderData(std::list<ARenderable*>* pList);
	void getCollisionData(std::list<ARenderable*>* pList);

private:
	CPowerUp_holder* m_pPowerUp_holder;
	CTexture* m_pTexture_powerUpHolder;


	/**
	 * Power Up Holders have two states within this container, active and inactive.
	 *
	 * Active is where they are flying around the screen bouncing off of the walls,
	 * and inactive is where they are sitting here waiting to be re-introduced to
	 * the world.
	 *
	 * When a player hits an active holder, it gives up its power to the player and
	 * then moves to the inactive list.
	 */
	std::list<CPowerUp_holder*> m_holder_active;
	std::list<CPowerUp_holder*> m_holder_inactive;
};

#endif /* CPOWERUP_CONTAINER_H_ */
