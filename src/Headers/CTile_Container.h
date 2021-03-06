/*
 * CGrid.h
 *
 *  Created on: Nov 19, 2013
 *      Author: zZelman
 */

#ifndef CTILE_CONTAINER_H_
#define CTILE_CONTAINER_H_

#include "include_sfml.h"
#include "IUpdateable.h"
#include "CTexture.h"
#include "CSprite.h"
#include <iostream>
#include <vector>
#include "rapidxml_utils.hpp"
#include "CTile.h"
#include "IGetCollisionData.h"
#include "IGetRenderData.h"
#include <list>

/**
 * TODO: This object needs to be re-writen to expand functionality.
 *
 * Custom Container for holding individual CTile.
 *
 * @see CTile
 */
class CTile_Container : public IUpdateable, public IGetRenderData, public IGetCollisionData
{
public:
	CTile_Container(std::string fileName);
	~CTile_Container();

	sf::Vector2<int> getGridSize(); // returns the total number of squares in (x, y)
	sf::Vector2<int> getGridSubSize(); // returns the individual tile size

	void update();

	void getCollisionData(std::list<ARenderable*>* pList);
	void getRenderData(std::list<ARenderable*>* pList);

	// * manipulates the screen values given into (x, y) grid coords
	// * values of posX and posY ARE OVERRIDEN
	void screenToGrid(int* posX, int* posY);

	// * checks if the given data is within a tile
	// * the sprite pointed to by pSprite is changed to the collision if true, null if not
	bool isCollision(const sf::Rect<float>& rect, CSprite*& pSprite);
	bool isCollision(const sf::Vector2<float>& point, CSprite*& pSprite);
	bool isCollision(float x, float y, CSprite*& pSprite);

private:
	// Initial (relative) file path to the Tiled XML map file directory
	std::string m_filePath;
	std::string m_fileName;			// name within the map file directory that is used for this CGrid
	std::string m_tileSetPath;		// path to the directory containing the tilesets

	CTexture* m_pTexture;
	std::list<CTile*> m_tiles;

	// uses the information gathered AFTER "parseFile()" has been called, and creates all of the
	//		tile objects that will be interacted with by the game
	void generateGrid();
	CTexture* generateGrid_texture();

	// takes the values of the (x,y) pos in 2D space and the Tiled grid num on the sprite sheet
	CSprite* generateGrid_sprite(int posX, int posY, int gridNum, CTexture* pTexture);

	// * helper function to gererateGrid_sprite
	// * In short, converts the "tile" node data recieved from Tiled XML, into a (col, row) sfml vector2
	//		texture coord which is used by CSprite (in m_currSub)
	// * NOTE: this function only works on/with converting the linear(ish) -non repeating- number recieved
	//		from Tiled into THIS program's CTexture currentSubImage coords
	//
	// * subNum 			= maximum number in (col, row)
	// * startingLength 	= starting number on the specific texture recieved from Tiled (can be >1)
	// * recievedNum		= the specific subImage number recieved from Tiled to be converted
	// * returnedPos		= CTexture's formated output (allocated elsewhere)
	void findSubImage(sf::Vector2<int>* subNum, int startingLength,
	                  int recievedNum, sf::Vector2<int>* returnedPos);

	// * helper function to generatedGrid_sprite
	// * calls the move() of the pSprite based on posX and posY to position the tile correctly on the screen
	void positionTile(CSprite* pSprite, int posX, int posY);

	// parses the given Tiled XML document into required data fields
	void parseFile();


	// Relevant data fields (in plane-old-data-structure) to "tileset" DOM
	struct tileset_imageData
	{
		std::string source;
		int width;
		int height;
	};
	struct tileset_data
	{
		int firstGrid;
		std::string name;
		int tileWidth;
		int tileHeight;
		struct tileset_imageData image;
	} m_sTilesetData;

	// * parse the "tileset" section of the DOM tree
	// * takes a pointer to the "tileset" node
	// * manipulates the data within "pData" allocated outside of this function
	void parseFile_tileset(rapidxml::xml_node<>* pTileSet, tileset_data* pData);


	// Relavent data fileds (in plane-old-data-structure) to "layer" DOM
	struct layer_data
	{
		std::string name;
		int width;
		int height;
		std::vector<std::vector<int> > tiles; // only the sprite sheet LENGTH number (not an obj)
	} m_sLayerData;

	// * parse the "layer" section of the DOM tree
	// * takes a pointer to the "layer" node
	// * manipulates the data within "pData" allocated outside of this function
	void parseFile_layer(rapidxml::xml_node<>* pLayer, layer_data* pData);


	// Relavent data fileds (in plane-old-data-structure) to "layer" DOM
	struct objectgroup_objectRect
	{
		int x;
		int y;
		int width;
		int height;
	};
	struct objectgroup_data
	{
		std::string name;
		int width;
		int height;
		std::vector<struct objectgroup_objectRect> rectObjects;
	} m_sObjectgroupData;

	// * parse the "objectgroup" section of the DOM tree
	// * takes a pointer to the "layer" node
	// * manipulates the data within "pData" allocated outside of this function
	void parseFile_objectgroup(rapidxml::xml_node<>* pObjectgroup, objectgroup_data* pData);

};

#endif /* CGRID_H_ */
