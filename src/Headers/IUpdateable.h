/*
 * IUpdatable.h
 *
 *  Created on: Oct 10, 2013
 *      Author: zZelman
 */

#ifndef IUPDATABLE_H_
#define IUPDATABLE_H_

/**
 * An interface for providing a common method to call to update
 * the state of an object.
 */
class IUpdateable
{
public:
	IUpdateable();
	virtual ~IUpdateable();

	virtual void update() = 0;
};


#endif /* IUPDATABLE_H_ */
