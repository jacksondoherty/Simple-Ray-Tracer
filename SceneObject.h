#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "Ray.h"
#include "Material.h"
using namespace std;


class SceneObject {
	protected:
		Material material;

		SceneObject();
		SceneObject(Material material);
		
	public:
		virtual ~SceneObject() = 0;
		virtual float intersection(Ray ray) = 0;
		virtual Vec3f getNormal(Vec3f point) const = 0; // todo: account for pt not on surface
		Material getMaterial() const;
		virtual void print() const = 0;
};

#endif /* SCENEOBJECT_H */