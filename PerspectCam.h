#ifndef PERSPECT_CAM_H
#define PERSPECT_CAM_H

#include "Camera.h"
using namespace std;


class PerspectCam: public Camera {
	private:
		Vec3f eyepoint;
		Vec3f gazeDirection;
		Vec3f upDirection;
		Vec3f rightDirection;
		float distanceToScreen;
		int upDimension;
		int downDimension;
		int leftDimension;
		int rightDimension;

	public:
		PerspectCam();
		PerspectCam(
			Vec3f eyepoint,
			Vec3f gazeDirection,
			Vec3f upDirection,
			float distanceToScreen,
			int upDimension,
			int downDimension,
			int leftDimension,
			int rightDimension);
		Ray getCameraRay(int i, int j) const;
};

#endif /* PERSPECT_CAM_H */