/*
 * CTexture.h
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "include_sfml.h"

/**
 * Wrapper class for SFML 2.1 Texture
 */
class CTexture : public sf::Texture
{
public:
	CTexture();

	/**
	 * @param fileName Relative full path to the texture image
	 * @param subSize LENGTH sub-image (x = width, y = height)
	 * @param subNum LENGTH number of sub images on the texture image
	 */
	CTexture(std::string fileName,
	         const sf::Vector2<int>& subSize,
	         const sf::Vector2<int>& subNum);
	CTexture(const CTexture& other);

	CTexture& operator=(const CTexture& other);

	/**
	 * LENGTH number of sub-section images on the full texture.
	 * x = cols; y = rows
	 */
	const sf::Vector2<int>& getSubNum() const;

	/**
	 * LENGTH of the sub-section image on the texture.
	 * x = width; y = height
	 */
	const sf::Vector2<int>& getSubSize() const;

private:
	/**
	 * LENGTH of the sub-section image on the texture.
	 * x = width; y = height
	 */
	sf::Vector2<int> m_subSize;

	/**
	 * LENGTH number of sub-section images on the full texture.
	 * x = cols; y = rows
	 */
	sf::Vector2<int> m_subNum;

	/**
	 * Uses API functions to load the image into memory.
	 */
	void load(std::string fileName);	// Relative path to the texture image
};

#endif /* CTEXTURE_H_ */
