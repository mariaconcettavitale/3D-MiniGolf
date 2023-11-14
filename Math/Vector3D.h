#pragma once
#ifndef __Vector3D_h
#define __Vector3D_h

/**
 * @class Vector3D
 * @brief Represents a 3D vector with various operations and properties.
 *
 * This class defines a 3D vector with components (x, y, z) and provides a wide range
 * of operations for manipulating and working with 3D vectors, including mathematical
 * operations, initialization, normalization, and more.
 *
 * @note This class is used for handling vector calculations in 3D space and includes
 *       various operator overloads to perform vector arithmetic.
 */

#include "../Math/Point3D.h"

class Vector3D {
public:
	Vector3D();
	~Vector3D();
	Vector3D(const Vector3D&);
	Vector3D(const float&, const float&, const float&);

	friend std::ostream& operator<<(std::ostream& out, const Vector3D& vec) {
		out << "<" << vec.x << "," << vec.y << "," << vec.z << ">";
		return out;
	}
	Vector3D& operator=(const Vector3D&);
	Vector3D& operator*=(const float&);
	Vector3D& operator/=(const float&);
	Vector3D operator -() const;
	Vector3D operator+(const Vector3D&);
	Vector3D operator-(const Vector3D&);
	Vector3D operator*(const Vector3D&);
	Vector3D operator*(const float&);
	Vector3D operator/(const float&);
	bool operator<=(const float&);

	Vector3D absolute();
	void normalize();
	void init(Vector3D);
	void init(float, float, float);
	void init(Point3D, Point3D);
	void Zero();
	Vector3D cross(const Vector3D&);
	float Length(void);
	float dot(const Vector3D&);
	void set(const GLfloat&, const GLfloat&, const GLfloat&);
	void CrossProduct(Vector3D, Vector3D*);
	void Normalize(void);
	void Reverse();
	void ScalarMultiply(float);
	float DotProduct(Vector3D);
	void getReflectionVector(Vector3D);
	void Add(Vector3D);

	bool isNormalized;
	float x;
	float y;
	float z;
};

#endif