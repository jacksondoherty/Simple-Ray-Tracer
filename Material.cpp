#include "Material.h"
#include <iostream>
using namespace std;


Material::Material(Color ambient, Color reflected, Color specular):
		ambientColor(ambient),
		reflectedColor(reflected),
		specularColor(specular) {}

Material::Material(const Material &obj):
	ambientColor(obj.ambientColor),
	reflectedColor(obj.reflectedColor),
	specularColor(obj.specularColor) {}

Color Material::getAmbient() {
	return ambientColor;
}

Color Material::getReflected() {
	return reflectedColor;
}

Color Material::getSpecular() {
	return specularColor;
}

void Material::print() const {
	cout << "Ambient Color: "; 
	ambientColor.print();
	cout << "ReflectedColor: ";
	reflectedColor.print();
	cout << "SpecularColor: ";
	specularColor.print();
}