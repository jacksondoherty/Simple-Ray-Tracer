#include "Ray.h"
using namespace std;


Ray::Ray(Vec3f origin, Vec3f direction): origin(origin), direction(direction) {
}

Ray& Ray::operator=(const Ray &obj) {
	if (this != &obj) {
		origin = obj.origin;
		direction = obj.direction;
	}

	return *this;
}