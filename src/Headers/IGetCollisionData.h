/*
 * IGetCollisionData.h
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#ifndef IGETCOLLISIONDATA_H_
#define IGETCOLLISIONDATA_H_

#include <list>
#include "ARenderable.h"

/**
 * A common interface from pulling relevant collision data from objects.
 */
class IGetCollisionData
{
public:
	virtual ~IGetCollisionData();

	/**
	 * All objects that implement this interface agree to allow their pointers to  Derived Classes of ARender
	 * to be placed within the given std::list so that they may be used for quad-tree collision detection
	 */
	virtual void getCollisiondata(std::list<ARenderable*>* pList) = 0;
};

#endif /* IGETCOLLISIONDATA_H_ */
