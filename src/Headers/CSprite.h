/*
 * CSprite.h
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#ifndef CSPRITE_H_
#define CSPRITE_H_

#include "include_sfml.h"
#include "CTexture.h"

/**
 * Wrapper class for SFML 2.1 Sprite.
 */
class CSprite : public sf::Sprite
{
public:
	/**
	 * @param pTexture texture that this sprite will be rendering with
	 * @param currSub LENGTH current sub-image being rendered
	 */
	CSprite(CTexture* pTexture,
	        const sf::Vector2<int>& currSub);
	~CSprite();
	CSprite(const CSprite& other);

	/**
	 * sets the current sub image being rendered from the texture
	 */
	void setSubImage(int col, int row);
	void setSubImage(const sf::Vector2<int>* newSub);

private:
	/**
	 * Full texture of this sprite.
	 *
	 * A subsection is rendered off of this
	 */
	CTexture* m_pTexture;

	/**
	 * LENGTH current sub section that is being rendered.
	 *
	 * x = col, y = row
	 */
	sf::Vector2<int> m_currSub;

	/**
	 * selects a sub-section of the texture
	 */
	void chooseSubImage();

};

#endif /* CSPRITE_H_ */
