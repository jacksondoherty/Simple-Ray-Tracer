#include "Vec3f.h"
#include <math.h>
#include <iostream>
using namespace std;


Vec3f::Vec3f(): x(0), y(0), z(0) {}

Vec3f::Vec3f(float x, float y, float z): x(x), y(y), z(z) {}

Vec3f::Vec3f(const Vec3f &obj): x(obj.x), y(obj.y), z(obj.z) {}

Vec3f& Vec3f::operator=(const Vec3f &obj) {
	if (this != &obj) {
		x = obj.x;
		y = obj.y;
		z = obj.z;
	}

	return *this;
}

Vec3f Vec3f::operator-(const Vec3f &obj) const {
	return Vec3f(x-obj.x, y-obj.y, z-obj.z);
}

Vec3f Vec3f::operator*(const Vec3f &obj) const {
	return Vec3f(x*obj.x, y*obj.y, z*obj.z);
}

Vec3f Vec3f::operator+(const Vec3f &obj) const {
	return Vec3f(x+obj.x, y+obj.y, z+obj.z);
}

Vec3f Vec3f::scale(float s) const {
	return Vec3f(s*x, s*y, s*z);
}

Vec3f Vec3f::negate() const {
	return Vec3f(-x, -y, -z);
}

float Vec3f::dotProduct(const Vec3f &obj) const {
	return x*obj.x + y*obj.y + z*obj.z;
}

Vec3f Vec3f::crossProduct(const Vec3f &obj) const {
	float i = y*obj.z - z*obj.y;
  float j = z*obj.x - x*obj.z;
  float k = x*obj.y - y*obj.x;

  return Vec3f(i, j, k);
}

float Vec3f::magnitude() const {
	return sqrt(x*x + y*y + z*z);
}

Vec3f Vec3f::normalize() {
	float magn = magnitude();
	x = x / magn;
	y = y / magn;
	z = z / magn;
	return *this;
}

void Vec3f::print() const {
	cout << "(" << x << "," << y << "," << z << ")" << endl;
}