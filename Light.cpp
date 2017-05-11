#include "Light.h"
#include <iostream>
using namespace std;


Light::Light(): color(Color(0, 0, 0)), direction(Vec3f(0, 0, 0)) {}

Light::Light(Color color, Vec3f direction): color(color), direction(direction) {
	direction.normalize();
}

Color Light::getColor() {
	return color;
}

Vec3f Light::getDirection() {
	return direction;
}

void Light::print() {
	cout << "Type: Light" << endl;
	cout << "Color: ";
	color.print();
	cout << "Direction: ";
	direction.print();
}