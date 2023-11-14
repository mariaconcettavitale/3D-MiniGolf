#pragma once
#ifndef __ModelLoader_h
#define __ModelLoader_h

#include "../Math/Point3D.h"
#include "../Math/Vector3D.h"
#include "../Libraries.h"

/**
 * @class ModelLoader
 * @brief Loads and renders 3D models, particularly 3DS Max models.
 *
 * This class is responsible for loading and rendering 3D models, especially those created
 * in 3DS Max. It contains properties to store vertices, polygons, texture coordinates, and
 * transformation information for the model. The class provides methods for initialization,
 * loading 3DS Max models, and rendering the model in the 3D space.
 *
 */

struct TexMapCoord
{
	float u;
	float v;
};

struct Poly
{
	unsigned short Index1;
	unsigned short Index2;
	unsigned short Index3;
};


class ModelLoader
{
private:	
	vector<Point3D> vertices;
	vector<Poly> polygons;
	vector<TexMapCoord> mapcoords;
	Point3D position;
	Vector3D scale;
	char name[20];
	int numVerts, numPolys;

public:
	ModelLoader(void);
	~ModelLoader() {};

	void init(Point3D pos, Vector3D sca);
	void Load3dsObject(const char* filename);
	void Draw(void);
};

#endif