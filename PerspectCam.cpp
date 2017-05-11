#include "PerspectCam.h"
using namespace std;


// todo: set a working, default camera
PerspectCam::PerspectCam():
		eyepoint(Vec3f(0,0,0)),
		gazeDirection(Vec3f(0,0,0)),
		upDirection(Vec3f(0,0,0)),
		rightDirection(Vec3f(0,0,0)),
		distanceToScreen(0),
		upDimension(0),
		downDimension(0),
		leftDimension(0),
		rightDimension(0) {}

PerspectCam::PerspectCam(
		Vec3f eyepoint,
		Vec3f gazeDirection,
		Vec3f upDirection,
		float distanceToScreen,
		int upDimension,
		int downDimension,
		int leftDimension,
		int rightDimension):

		eyepoint(eyepoint),
		gazeDirection(gazeDirection.normalize()),
		upDirection(upDirection.normalize()),
		distanceToScreen(distanceToScreen),
		upDimension(upDimension),
		downDimension(downDimension),
		leftDimension(leftDimension),
		rightDimension(rightDimension) {

	rightDirection = gazeDirection.crossProduct(upDirection);
	upDirection = rightDirection.crossProduct(gazeDirection);
}

Ray PerspectCam::getCameraRay(int i, int j) const {
	Vec3f wdir = gazeDirection.scale(-1);
	Vec3f vdir = upDirection;
	Vec3f udir = rightDirection;
	float d = distanceToScreen;
	float l = leftDimension;
	float b = downDimension;

	float u = l + i + 0.5;
	float v = b + j + 0.5;

	Vec3f rayDir = wdir.scale(-d) + udir.scale(u) + vdir.scale(v);

	return Ray(eyepoint, rayDir);
}