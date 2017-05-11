#ifndef RAY_H
#define RAY_H

#include "Vec3f.h"
using namespace std;


class Ray {
	public:	
		Vec3f origin;
		Vec3f direction;
		Ray(Vec3f origin, Vec3f direction);
		Ray& operator=(const Ray &obj);
};

#endif /* RAY_H */

