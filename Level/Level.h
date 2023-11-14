#pragma once
#ifndef __Level_h
#define __Level_h

/**
 * @class Level
 * @brief Represents a level in the mini-golf engine.
 *
 * This class defines the properties od each level in a mini-golf game, such as the level name,
 * a collection of tiles, a collection of cups, the current tile, and the par score.
 * The class provides methods to draw the level and set textures.
 */

#include "Tee.h"
#include "Tile.h"
#include "Cup.h"

class Level
{
public:
	string levelName;
	std::map<int, Tile> tileSet;
	
	Cup cups;
	Tee tees;
	int currentTile;
	int Par;

	void drawLevel();
	void setTextures();
	
};

#endif