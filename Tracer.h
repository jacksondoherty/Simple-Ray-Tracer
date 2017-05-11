#ifndef TRACER_H
#define TRACER_H

#include "Scene.h"
#include "Color.h"
using namespace std;


class Tracer {
	private:
		Scene *scene;
		int maxRecursions;
		Color castRay(Ray ray, int recursions);
		void fillPixel(int row, int col, Color color);
		Color calculateColor(SceneObject *object, Vec3f norm, Ray ray, float t);
		Ray reflectionRay(Ray ray, Vec3f n, float t);
		float clamp(float s);
	public:
		Tracer();
		Tracer(Scene *scene);
		~Tracer();
		void setMaxRecursions(int num);
		void trace();
};

#endif /* TRACER_H */