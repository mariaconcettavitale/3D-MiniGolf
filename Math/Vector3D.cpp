#include "../Libraries.h"
#include "Vector3D.h"

Vector3D::Vector3D() : x(0), y(0), z(0) {
}

void Vector3D::init(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->isNormalized = false;
}

void Vector3D::init(Vector3D vec)
{
	this->init(vec.x, vec.y, vec.z);
	this->isNormalized = false;
}

void Vector3D::init(Point3D pt1, Point3D pt2)
{
	this->init(pt2.x - pt1.x,
		pt2.y - pt1.y,
		pt2.z - pt1.z); // Build a Vector directed from pt1 to pt2
}

Vector3D::~Vector3D() {
}

Vector3D::Vector3D(const Vector3D& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3D::Vector3D(const float& nx, const float& ny, const float& nz) {
	x = nx;
	y = ny;
	z = nz;
}

Vector3D& Vector3D::operator=(const Vector3D& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vector3D& Vector3D::operator*=(const float& rhs) {
	*this = (*this) * rhs;
	return *this;
}

Vector3D& Vector3D::operator/=(const float& rhs) {
	*this = (*this) / rhs;
	return *this;
}

Vector3D Vector3D::operator-() const {
	Vector3D ans;
	ans.x = -x;
	ans.y = -y;
	ans.z = -z;
	return ans;
}

Vector3D Vector3D::operator+(const Vector3D& other) {
	Vector3D ans;
	ans.x = x + other.x;
	ans.y = y + other.y;
	ans.z = z + other.z;
	return ans;
}

Vector3D Vector3D::operator-(const Vector3D& other) {
	Vector3D ans;
	ans.x = x - other.x;
	ans.y = y - other.y;
	ans.z = z - other.z;
	return ans;
}

Vector3D Vector3D::operator*(const Vector3D& other) {
	Vector3D ans;
	ans.x = x * other.x;
	ans.y = y * other.y;
	ans.z = z * other.z;
	return ans;
}

Vector3D Vector3D::operator*(const float& multip) {
	Vector3D ans;
	ans.x = x * multip;
	ans.y = y * multip;
	ans.z = z * multip;
	return ans;
}

Vector3D Vector3D::operator/(const float& divisor) {
	Vector3D ans;
	if (divisor != 0) {
		if (x == 0) {
			ans.x = 0;
		}
		else {
			ans.x = x / divisor;
		}
		if (y == 0) {
			ans.y = 0;
		}
		else {
			ans.y = y / divisor;
		}
		if (z == 0) {
			ans.z = 0;
		}
		else {
			ans.z = z / divisor;
		}
	}
	else if (ans.x == 0 && ans.y == 0 && ans.z == 0 && divisor == 0) {
		ans = Vector3D(0, 0, 0);
	}
	else {
		cerr << "Error: vector division by zero." << endl;
		exit(1);
	}
	return ans;
}

// solely made to compare against zero, may make Vec3.Zero() in future
bool Vector3D::operator<=(const float& num) {
	return (x <= num && y <= num && z <= num);
}

Vector3D Vector3D::absolute() {
	return Vector3D(abs(x), abs(y), abs(z));
}

Vector3D Vector3D::cross(const Vector3D& other) {
	Vector3D ans;
	// Compute The Cross Product To Give Us A Surface Normal
	ans.x = ((*this).y * other.z) - ((*this).z * other.y);
	ans.y = ((*this).z * other.x) - ((*this).x * other.z);
	ans.z = ((*this).x * other.y) - ((*this).y * other.x);
	return ans;
}

float Vector3D::dot(const Vector3D& other) {
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

void Vector3D::normalize() {

	if (this->isNormalized)
		return;

	float d = (x * x) + (y * y) + (z * z);
	d = (float)sqrt(d);
	(*this) = (*this) / d;
	this->isNormalized = true;
}

void Vector3D::set(const float& nx, const float& ny, const float& nz) {
	x = nx;
	y = ny;
	z = nz;
}

void Vector3D::ScalarMultiply(float k)
{
	this->x *= k;
	this->y *= k;
	this->z *= k;
	this->isNormalized = false;
}

void Vector3D::Reverse()
{
	this->ScalarMultiply(-1);
}


void Vector3D::CrossProduct(Vector3D vec, Vector3D* result)
{
	result->x = ((this->y * vec.z) - (this->z * vec.y));
	result->y = -((this->x * vec.z) - (this->z * vec.x));
	result->z = ((this->x * vec.y) - (this->y * vec.x));
	result->isNormalized = false;
}

float Vector3D::Length(void)
{
	return (
		(float)sqrtf(this->x * this->x + this->y * this->y + this->z * this->z));
}

void Vector3D::Normalize(void)
{
	if (this->isNormalized)
		return;

	float factor = this->Length();
	
	if (factor < EPSILON5)
		return;
	this->ScalarMultiply(1.0f / factor);
	this->isNormalized = true;
}

void Vector3D::Zero()
{
	this->x = this->y = this->z = 0.0f;
}

float Vector3D::DotProduct(Vector3D vec)
{
	return ((this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z));
}

void Vector3D::Add(Vector3D vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->isNormalized = false;
}

// Calculate collision resultant vector by formula R= I - 2*(I dot N)*N
void Vector3D::getReflectionVector(Vector3D normalVector)
{
	Vector3D firstFactor(this->x, this->y, this->z); // firstFactor = Reflect(i.e this) = I
	firstFactor.Reverse();		  // firstFactor = -I
	float multiple =
		2 * firstFactor.DotProduct(normalVector); // multiple = 2*(-I dot N)
	normalVector.ScalarMultiply(multiple);		// N = 2*(-I dot N)*N
	this->Add(normalVector); // R = N + I = 2*(-I dot N)*N + I
}
