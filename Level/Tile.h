#pragma once
#ifndef __Tile_h
#define __Tile_h

/**
 * @class Tile
 * @brief Defines a tile on a level with associated properties.
 *
 * This class represents a tile within a level.
 * It includes properties such as the tile's type, identifier, vertices, edges, normals,
 * neighbors, and texture information. The class is responsible for defining the characteristics
 * of a tile and methods for collision detection and rendering.
 *
 */

#include "../Math/Point3D.h"
#include "../Math/Vector3D.h"
#include "../Textures&Models/TextureHandler.h"
#include "../Libraries.h"

class Tile
{
private:
	TextureHandler textureobj;
	string tileType;
	int tileID;
	int numberOfVertices;
	Vector3D normal;


public:
	
	std::map<int, Point3D> vertices;
	std::map<int, Vector3D> edges;
	std::map<int, Vector3D> edgeNormals;
	std::map<int, int> neighbours;

	Tile();
	~Tile() {};

	void setTileType(string);
	string getTileType();
	void setTileID(int);
	int getTileId();
	void setNumberOfVertices(int);
	int getNumberOfVertices();
	Vector3D getNormal();
	void setNormal(Vector3D);
	void updateNormal(Vector3D);
	void normalizeNorm();
	
	void initCollisionDetectionEdges(void);
	void draw(float, float, float);

	

};

#endif