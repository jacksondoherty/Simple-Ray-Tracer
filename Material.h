#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
using namespace std;


class Material {
	private:
		Color ambientColor;
		Color reflectedColor;
		Color specularColor;
	public:
		Material(
				Color ambient = Color(0,0,0),
				Color reflected = Color(0,0,0),
				Color specular = Color(0,0,0)
		);
		Material(const Material &obj);
		Color getAmbient();
		Color getReflected();
		Color getSpecular();
		void print() const;
};

#endif /* MATERIAL_H */

