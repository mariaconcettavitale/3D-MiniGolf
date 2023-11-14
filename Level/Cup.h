#pragma once
#ifndef __Cup_h
#define __Cup_h

/**
 * @class Cup
 * @brief Represents a  hole in the 3D mini-golf game.
 *
 * This class is used to define a  hole in a 3D mini-golf game. It contains properties
 * to identify the cup, its location (vertex), and the normal vector for rendering and gameplay.
 * The `draw` method is used to render the cup based on the number of triangles provided.
 */

#include "../Math/Point3D.h"
#include "../Math/Vector3D.h"

class Cup {
public:
	int cupID;
	int tileID;
	Point3D vertex;
	Vector3D normal;

	void draw(int triangleCount);
};

#endif