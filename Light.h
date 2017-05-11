#ifndef LIGHT_H
#define LIGHT_H

#include "Color.h"
#include "Vec3f.h"
using namespace std;


class Light {
	private:
		Color color;
		Vec3f direction;

	public:
		Light();
		Light(Color color, Vec3f direction);
		Color getColor();
		Vec3f getDirection();
		void print();
};

#endif /* LIGHT_h */