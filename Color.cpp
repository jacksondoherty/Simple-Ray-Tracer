#include "Color.h"
#include <iostream>
using namespace std;


Color::Color(): r(0), g(0), b(0) {}

Color::Color(float r, float g, float b): r(r), g(g), b(b) {}

Color::Color(const Color &obj): r(obj.r), g(obj.g), b(obj.b) {}

Color& Color::operator=(const Color &obj) {
	if (this != &obj) {
		r = obj.r;
		g = obj.g;
		b = obj.b;
	}

	return *this;
}

Color Color::operator*(const Color &obj) const {
	return Color(r*obj.r, g*obj.g, b*obj.b);
}

Color Color::operator+(const Color &obj) const {
	return Color(r+obj.r, g+obj.g, b+obj.b);
}

Color Color::scale(float s) const {
	return Color(s*r, s*g, s*b);
}

float clampZeroOne(float f) {
	if (f < 0) {
		return 0;
	} else if (f > 1) {
		return 1;
	} else {
		return f;
	}
}

void Color::clamp() {
	r = clampZeroOne(r);
	g = clampZeroOne(g);
	b = clampZeroOne(b);
}

void Color::print() const {
	cout << "(" << r << "," << g << "," << b << ")" << endl;
}
