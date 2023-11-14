#pragma once
#ifndef __Tee_h
#define __Tee_h

/**
 * @class Tee
 * @brief Represents a tee marker in the golf game.
 *
 * This class defines a tee marker, typically used in a golf game. It includes properties
 * such as the tee's identifier, the associated tile's identifier, the tee's location (vertex),
 * and the normal vector for rendering. The class is responsible for representing tee markers.
 *
 * @note The `Tee` class is used to identify and position tee markers in the game.
 */

#include "../Math/Point3D.h"
#include "../Math/Vector3D.h"


class Tee {
public:
	int teeID;
	int tileID;
	Point3D vertex;
	Vector3D normal;

	Tee() {};
	~Tee() {};

	
};
#endif