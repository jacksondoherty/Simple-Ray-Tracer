#include "OrthoCam.h"
using namespace std;


OrthoCam::OrthoCam() {}

OrthoCam::OrthoCam(int screenWidth, int screenLength): 
		Camera(screenWidth, screenLength) {}

//	Ortho cam is fixed looking down negative z
//	axis with bottom left corner at 0,0,0 in world space
Ray OrthoCam::getCameraRay(int i, int j) const {
	Vec3f origin = Vec3f(i, j, 0);
	Vec3f direction = Vec3f(0, 0, -1);
	return Ray(origin, direction);
}