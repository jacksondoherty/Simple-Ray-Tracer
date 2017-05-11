#include "SceneObject.h"
using namespace std;


SceneObject::SceneObject(): material(Material()) {}

SceneObject::SceneObject(Material material): material(material) {}

SceneObject::~SceneObject() {}

Material SceneObject::getMaterial() const {
	return material;
}