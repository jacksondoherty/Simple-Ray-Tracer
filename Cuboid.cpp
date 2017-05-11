#include "Cuboid.h"
#include <math.h>
#include <iostream>
using namespace std;


Cuboid::Cuboid(): pointU(Vec3f(0,0,0)), pointV(Vec3f(0,0,0)), cachedObj(NULL) {}

Cuboid::Cuboid(Vec3f u, Vec3f v, Material material): 
		SceneObject(material), 
		pointU(u),
		pointV(v),
		cachedObj(NULL) {

	Vec3f a(u.x, u.y, v.z);
	Vec3f b(u.x, u.y, u.z);
	Vec3f c(v.x, u.y, u.z);
	Vec3f d(v.x, u.y, v.z);
	Vec3f e(u.x, v.y, u.z);
	Vec3f f(v.x, v.y, u.z);
	Vec3f g(u.x, v.y, v.z);
	Vec3f h(v.x, v.y, v.z);

	triangles.push_back(Triangle(b,c,a, material));
	triangles.push_back(Triangle(d,a,c, material));
	triangles.push_back(Triangle(b,a,e, material));
	triangles.push_back(Triangle(g,e,a, material));
	triangles.push_back(Triangle(f,h,c, material));
	triangles.push_back(Triangle(d,c,h, material));
	triangles.push_back(Triangle(g,a,d, material));
	triangles.push_back(Triangle(h,g,d, material));
	triangles.push_back(Triangle(f,e,g, material));
	triangles.push_back(Triangle(f,g,h, material));
	triangles.push_back(Triangle(b,e,c, material));
	triangles.push_back(Triangle(c,e,f, material));
}

float Cuboid::intersection(Ray ray) {
	cachedObj = NULL; // reset
	float minTValue = INFINITY;
	for (auto it = triangles.begin(); it != triangles.end() ; ++it) {
		float t = it->intersection(ray);
		if (t < minTValue) {
			minTValue = t;
			cachedObj = &(*it);
		}
	}
	return minTValue;
}

// todo: throw exception on non intersecting point
Vec3f Cuboid::getNormal(Vec3f point) const {
	if (cachedObj == NULL) {
		cout << "Error: normal asked from non-intersecting point" << endl;
		return Vec3f(-1, -1, -1);
	}

	return cachedObj->getNormal(point);
}

void Cuboid::print() const {
	cout << "Type: Cuboid" << endl;
	cout << "Point U: ";
	pointU.print();
	cout << "Point V: ";
	pointV.print();
	cout << "Material: " << endl;
	material.print();
}