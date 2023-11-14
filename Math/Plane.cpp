#include "Plane.h"

void Plane::init(Point3D pt, Vector3D n)
{
	this->pointInPlane.init(pt);
	this->normal.init(n);
	if (!n.isNormalized)
		this->normal.Normalize();
}


// Compute the signed distance from a point to the plane.
float Plane::ComputePointPlaneHalfSpace(Point3D pt)
{


	float value = this->normal.x * (pt.x - this->pointInPlane.x) +
	this->normal.y * (pt.y - this->pointInPlane.y) +
	this->normal.z * (pt.z - this->pointInPlane.z);

	return value;
}


// Compute the Y-coordinate on the plane for a given X and Z coordinate.
float Plane::ComputeSafeYonPlane(float ptx, float ptz)
{
	float pty = (-this->normal.x * (ptx - this->pointInPlane.x) -
	this->normal.z * (ptz - this->pointInPlane.z) +
	this->normal.y * this->pointInPlane.y) / this->normal.y;
	
	return pty;
}
