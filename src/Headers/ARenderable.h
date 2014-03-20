/*
 * IRenderable.h
 *
 *  Created on: Oct 10, 2013
 *      Author: zZelman
 */

#ifndef ARENDER_H_
#define ARENDER_H_

#include "include_sfml.h"
#include "CTexture.h"
#include "CSprite.h"

/**
 * An abstract base class for all things that can be rendered.
 *
 * Holds API wrapper class for rendering CSprite.
 *
 * @see CSprite
 */
class ARenderable
{
public:
	/**
	 * @param pTexture A API wrapper class that is allocated elsewhere that this renderable
	 * base class with reference with its CSprite
	 * @param currSub The starting current sub image being rendered by the CSprite
	 */
	ARenderable(CTexture* pTexture,
	            const sf::Vector2<int>& currSub);

	/**
	 * if this constructor is used, note that this object then takes responsibility
	 * for the CSprite*
	 */
	ARenderable(CSprite* pSprite);
	virtual ~ARenderable();

	/**
	 * Returns the API wrapper version of the sprite
	 *
	 * @see m_pSprite
	 */
	CSprite* const getSprite() const;

	/**
	 * Returns the API version of this sprite
	 *
	 * @see m_pSprite
	 */
	sf::Sprite* const getSprite_API() const;
	sf::FloatRect getGlobalBounds();

	const sf::View& getView() const;
	bool getHasView() const;

	/**
	 * Forwards the position coords into the API sprite to re-set
	 * the position of the sprite in GLOBAL coords
	 */
	void setPosition(float x, float y);

protected:

	/**
	 * This class assumes responsibility for this CSprite object
	 */
	CSprite* m_pSprite;

	/**
	 * API subsection of the world being rendered, if this ARenderable has one.
	 *
	 * The bool 'hasView' controlls wheither or not this variable has
	 * meaningfull data within it, ie will be used durring rendering.
	 *
	 * @see hasView
	 */
	sf::View m_view;

	/**
	 * True = m_view has meaningful render data ; False = m_view is garbage.
	 *
	 * @see m_view
	 */
	bool hasView;
};


#endif /* IRENDERABLE_H_ */
