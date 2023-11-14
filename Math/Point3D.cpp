#include "../Libraries.h"
#include "Point3D.h"

Point3D::Point3D()
{
	this->Zero();
}

Point3D::Point3D(float x, float y, float z)
{
	this->init(x, y, z);
}

void Point3D::Zero()
{
	this->x = this->y = this->z = 0.0f;
}

void Point3D::init(Point3D pt)
{
	this->init(pt.x, pt.y, pt.z);
}

void Point3D::init(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

}

bool Point3D::isEqual(Point3D pt)
{
	float val1 = (x * x) + (y * y) + (z * z);
	float val2 = (pt.x * pt.x) + (pt.y * pt.y) + (pt.z * pt.z);
	if ((val1 >= (val2 - EPSILON4)) && (val1 <= (val2 + EPSILON4)))
		return true;
	else
		return false;
}

Point3D Point3D::operator*(const float& factor)
{
	Point3D ans;
	ans.x = x * factor;
	ans.y = y * factor;
	ans.z = z * factor;

	return ans;
}

Point3D Point3D::operator/(const float& factor)
{
	return Point3D(x / factor, y / factor, z / factor);
}

Point3D Point3D::operator+(const Point3D& pnt)
{
	return Point3D(x + pnt.x, y + pnt.y, z + pnt.z);
}

Point3D Point3D::operator-(const Point3D& pnt)
{
	return Point3D(x - pnt.x, y - pnt.y, z - pnt.z);
}

Point3D Point3D::operator-() const
{
	return Point3D(-x, -y, -z);
}

Point3D& Point3D::operator*=(const float& factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

Point3D& Point3D::operator/=(const float& factor)
{
	x /= factor;
	y /= factor;
	z /= factor;
	return *this;
}

Point3D& Point3D::operator+=(const Point3D& pnt)
{
	x += pnt.x;
	y += pnt.y;
	z += pnt.z;
	return *this;
}

Point3D& Point3D::operator-=(const Point3D& pnt)
{
	x -= pnt.x;
	y -= pnt.y;
	z -= pnt.z;
	return *this;
}

Point3D operator*(float multiple, Point3D& p)
{
	return p * multiple;
}

