/*
 * AUpdate.h
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#ifndef AUPDATE_H_
#define AUPDATE_H_

#include "IUpdateable.h"

/**
 * Wrapper class to IUpdatable which only adds 1 variable.
 *
 * @see m_isFirstUpdate
 */
class AUpdate : public IUpdateable
{
public:
	AUpdate();
	virtual ~AUpdate();

	virtual void update() = 0;

protected:

	/**
	 * Boolean to keep track of first-time update cycles
	 *
	 * This is intended to prevent time-sensitive things from freaking out from the objects
	 * init time to the first update
	 */
	bool m_isFirstUpdate;
};

#endif /* AUPDATE_H_ */
