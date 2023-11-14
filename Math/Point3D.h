#pragma once
#ifndef __Point3D_h
#define __Point3D_h

/**
 * @class Point3D
 * @brief Represents a 3D point in Cartesian coordinates.
 *
 * This class defines a point in three-dimensional space with coordinates (x, y, z).
 * It provides various operations for manipulating and working with 3D points,
 * including arithmetic operations and equality checks.
 *
 * @note This class also defines several operator overloads to make working with
 *       Point3D objects more convenient, such as addition, subtraction, and
 *       scalar multiplication.
 */
#include "../Libraries.h"

class Point3D
{
public:
	float x, y, z;

	Point3D();

	Point3D(float, float, float);
	~Point3D() {};

	void Zero();
	void init(Point3D);
	void init(float, float, float);
	bool isEqual(Point3D pt);

	Point3D& operator-=(const Point3D&);
	Point3D& operator*=(const float&);
	Point3D& operator/=(const float&);
	Point3D& operator+=(const Point3D&);
	Point3D operator-() const;
	Point3D operator*(const float&);
	Point3D operator/(const float&);
	Point3D operator+(const Point3D&);
	Point3D operator-(const Point3D&);

};


Point3D operator*(float&, Point3D&);
#endif