#ifndef PLANE_H
#define PLANE_H

#include "SceneObject.h"
#include "Vec3f.h"
using namespace std;


class Plane: public SceneObject {
	private:
		Vec3f normal;
		Vec3f passingPoint;
	public:
		Plane();
		Plane(Vec3f normal, Vec3f passingPoint, Material material);
		float intersection(Ray ray);
		Vec3f getNormal(Vec3f point) const;
		void print() const;
};

#endif /* PLANE_H */