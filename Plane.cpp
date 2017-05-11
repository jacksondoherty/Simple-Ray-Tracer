#include "Plane.h"
#include <math.h>
#include <iostream>
using namespace std;


Plane::Plane(): normal(Vec3f(0,0,0)), passingPoint(Vec3f(0,0,0)) {}

Plane::Plane(Vec3f normal, Vec3f passingPoint, Material material): 
		SceneObject(material),
		normal(normal), 
		passingPoint(passingPoint) {}

float Plane::intersection(Ray ray) {
	Vec3f l = ray.direction;
	Vec3f l0 = ray.origin;
	Vec3f n = normal;
	Vec3f p0 = passingPoint;

	float t = (p0 - l0).dotProduct(n) / (l.dotProduct(n));

	if (t <= 0.001) {
		return INFINITY;
	}

	return t;
}

Vec3f Plane::getNormal(Vec3f point) const {
	return normal;
}

void Plane::print() const {
	cout << "Type: Plane" << endl;
	cout << "Normal: ";
	normal.print();
	cout << "Passing through point: ";
	passingPoint.print();
	cout << "Material: " << endl;
	material.print();
}