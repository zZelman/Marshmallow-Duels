/*
 * IGetRenderData.h
 *
 *  Created on: Jan 1, 2014
 *      Author: zZelman
 */

#ifndef IGETRENDERDATA_H_
#define IGETRENDERDATA_H_

#include "include_sfml.h"
#include "ARenderable.h"
#include <list>

/**
 * A common interface for pulling relavent rendering information out of objects.
 */
class IGetRenderData
{
public:
	virtual ~IGetRenderData();

	/**
	 * Fills the std::list with objects that need to be rendered
	 */
	virtual void getRenderData(std::list<ARenderable*>* pList) = 0;
};

#endif /* IGETRENDERDATA_H_ */
