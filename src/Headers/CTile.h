/*
 * CTIle.h
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#ifndef CTILE_H_
#define CTILE_H_

#include "ARenderable.h"
#include "AUpdate.h"
#include "DPhysics.h"
#include "CSprite.h"

/**
 * Rectangle of rigid space that is a rendered platform or wall
 */
class CTile: public ARenderable, public AUpdate
{
public:
	/**
	 * @param pTexture texture that this sprite will be rendering with
	 * @param currSub LENGTH current sub-image being rendered
	 */
	CTile(CTexture* pTexture,
	      const sf::Vector2<int>& currSub);

	/**
	 * If this constructor is used, CTile assumes responsibility
	 * for the CSprite
	 */
	CTile(CSprite* pSprite);
	~CTile();

	void update();
};

#endif /* CTILE_H_ */
