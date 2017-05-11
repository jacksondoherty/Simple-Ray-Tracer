#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "SceneObject.h"
#include "Vec3f.h"
using namespace std;


class Triangle: public SceneObject {
	private:
		Vec3f pointA;
		Vec3f pointB;
		Vec3f pointC;
	public:
		Triangle();
		Triangle(Vec3f pointA, Vec3f pointB, Vec3f pointC, Material material);
		float intersection(Ray ray);
		// todo: throw exception on non intersecting point
		// todo: remove point parameter but keep polymorphism
		Vec3f getNormal(Vec3f point) const;
		void print() const;
};

#endif /* TRIANGLE_H */