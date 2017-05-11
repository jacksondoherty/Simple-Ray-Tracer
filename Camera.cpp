#include "Camera.h"
#include <iostream>


const int defaultWidth = 1024;
const int defaultLength = 1024;

Camera::Camera(): screenWidth(defaultWidth), screenLength(defaultLength) {}

Camera::Camera(int screenWidth, int screenLength): 
		screenWidth(screenWidth),
		screenLength(screenLength) {}

Camera::~Camera() {}

int Camera::getScreenWidth() const {
	return screenWidth;
}

int Camera::getScreenLength() const {
	return screenLength;
}