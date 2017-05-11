#include "Triangle.h"
#include "Vec3f.h"
#include <math.h>
#include <iostream>
using namespace std;


Triangle::Triangle(): pointA(Vec3f(0,0,0)), pointB(Vec3f(0,0,0)), pointC(Vec3f(0,0,0)) {}

Triangle::Triangle(Vec3f pointA, Vec3f pointB, Vec3f pointC, Material material): 
		SceneObject(material),
		pointA(pointA), 
		pointB(pointB),
		pointC(pointC) {}

float Triangle::intersection(Ray ray) {
	float a = pointA.x - pointB.x;
	float b = pointA.y - pointB.y;
	float c = pointA.z - pointB.z;
	float d = pointA.x - pointC.x;
	float e = pointA.y - pointC.y;
	float f = pointA.z - pointC.z;
	float g = ray.direction.x;
	float h = ray.direction.y;
	float i = ray.direction.z;
	float j = pointA.x - ray.origin.x;
	float k = pointA.y - ray.origin.y;
	float l = pointA.z - ray.origin.z;

	float M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);

	float t = -(f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;
	if (t <= 0.001) {
		return INFINITY;
	}
	float gamma = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
	if (gamma < 0 || gamma > 1) {
		return INFINITY;
	}
	float beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
	if (beta < 0 || beta > 1-gamma) {
		return INFINITY;
	}

	return t;
}

// todo: remove point parameter
// todo: throw exception on non intersecting point
Vec3f Triangle::getNormal(Vec3f point) const {
	Vec3f result = (pointB-pointC).crossProduct(pointA-pointB);
	result.normalize();
	return result;
}

void Triangle::print() const {
	cout << "Type: Triangle" << endl;
	cout << "Point A: ";
	pointA.print();
	cout << "Point B: ";
	pointB.print();
	cout << "Point C: ";
	pointC.print();
	cout << "Material: " << endl;
	material.print();
}