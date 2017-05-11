#ifndef SPHERE_H
#define SPHERE_H

#include "SceneObject.h"
#include "Vec3f.h"
using namespace std;


class Sphere: public SceneObject {
	private:
		float radius;
		Vec3f center;
	public:
		Sphere();
		Sphere(float radius, Vec3f center, Material material);
		float intersection(Ray ray);
		Vec3f getNormal(Vec3f point) const; // todo: throw exception on non intersecting point
		void print() const;
};

#endif /* SPHERE_H */