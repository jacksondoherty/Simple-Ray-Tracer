#ifndef CUBOID_H
#define CUBOID_H

#include "SceneObject.h"
#include "Vec3f.h"
#include "Triangle.h"
#include <vector>
using namespace std;


class Cuboid: public SceneObject {
	private:
		Vec3f pointU;
		Vec3f pointV;
		vector<Triangle> triangles;
		int cachedIndex; // -1 flag
	public:
		Cuboid();
		Cuboid(Vec3f u, Vec3f v, Material material);
		float intersection(Ray ray);
		Vec3f getNormal(Vec3f point) const; // todo: throw exception on non intersecting point
		void print() const;

};

#endif /* CUBOID_H */