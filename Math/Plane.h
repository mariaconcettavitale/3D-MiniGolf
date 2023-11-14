#pragma once
#ifndef __Plane_h
#define __Plane_h

/**
 * @class Plane
 * @brief Represents a 3D plane with a point and a normal vector.
 *
 * This class defines a 3D plane characterized by a point lying on the plane and
 * a normal vector perpendicular to the plane's surface. It includes methods to initialize
 * the plane, compute the position of a point in relation to the plane, and
 * calculate the safe Y-coordinate on the plane for a given (x, z) position.
 *
 */

#include "../Math/Point3D.h"
#include "../Math/Vector3D.h"


class Plane
{
public:
	Point3D pointInPlane;		// point on the plane
	Vector3D normal;		    // normal to the plane

	Plane() {};
	~Plane() {};

	void init(Point3D, Vector3D);
	float ComputePointPlaneHalfSpace(Point3D);
	float ComputeSafeYonPlane(float ptx, float ptz);


};

#endif