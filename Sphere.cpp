#include "Sphere.h"
#include <math.h>
#include <iostream>
using namespace std;


Sphere::Sphere(): radius(0), center(Vec3f(0,0,0)) {}

Sphere::Sphere(float radius, Vec3f center, Material material): 
		SceneObject(material),
		radius(radius), 
		center(center) {}

float Sphere::intersection(Ray ray) {
	Vec3f d = ray.direction;
	Vec3f e = ray.origin;
	Vec3f c = center;
	float R = radius;

	// check discriminant
	float bSquared = (d.dotProduct(e-c))*(d.dotProduct(e-c));
	float fourAC = (d.dotProduct(d)) * ((e-c).dotProduct(e-c)-R*R);
	float discriminant = bSquared - fourAC;
	if (discriminant < 0) {
		return INFINITY;
	}

	// calculate t
	// use subtraction point because looking for nearest t
	float top = d.negate().dotProduct(e-c) - sqrt(discriminant);
	float t = top / d.dotProduct(d);
	if (t <= 0.001) { // to prevent intersection with self
		return INFINITY;
	}
	return t;
}

// todo: throw exception on non intersecting point
Vec3f Sphere::getNormal(Vec3f point) const {
	float factor = 1.0f/radius;
	Vec3f result = (point-center).scale(factor);
	return result;
}

void Sphere::print() const {
	cout << "Type: Sphere" << endl;
	cout << "Radius: " << radius << endl;
	cout << "Center: ";
	center.print();
	cout << "Material: " << endl;
	material.print();
}