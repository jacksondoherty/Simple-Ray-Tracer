#ifndef ORTHO_CAM_H
#define ORTHO_CAM_H

#include "Camera.h"
using namespace std;


class OrthoCam: public Camera {
	public:
		OrthoCam();
		OrthoCam(int screenWidth, int screenLength);
		//	Ortho cam is fixed looking down negative z
		//	axis with bottom left corner at 0,0,0 in world space
		Ray getCameraRay(int i, int j) const;
};

#endif /* ORTHO_CAM_H */