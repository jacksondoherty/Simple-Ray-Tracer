#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3f.h"
#include "Ray.h"
using namespace std;


class Camera {
	protected:
		int screenWidth;
		int screenLength;

		Camera();
		Camera(int screenWidth, int ScreenLength);

	public:
		virtual ~Camera() = 0;
		virtual Ray getCameraRay(int i, int j) const = 0;
		int getScreenWidth() const;
		int getScreenLength() const;
};

#endif /* CAMERA_H */