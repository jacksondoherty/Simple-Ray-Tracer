#include "Tracer.h"
#include <cstddef>
#include "Scene.h"
#include <iostream>
#include "Ray.h"
#include <GL/glut.h>
#include <math.h>
using namespace std;


#define	checkImageWidth 1024
#define	checkImageHeight 1024
extern GLubyte checkImage[checkImageHeight][checkImageWidth][3];
extern void display();
extern void makeCheckImage();

const int defaultMaxRecurs = 4;

Tracer::Tracer(): scene(NULL) {}

Tracer::Tracer(Scene *scene): scene(scene), maxRecursions(defaultMaxRecurs) {}

// Precond: scene camera has been properly set
void Tracer::trace() {
	Camera *camera = scene->getCamera();
	for (int j = 0; j < camera->getScreenLength(); j++) {
		for (int i = 0; i < camera->getScreenWidth(); i++) {

			// create ray
			Ray cameraRay = camera->getCameraRay(i, j);

			Color col = castRay(cameraRay, 0);
			if (col.r < 0 && col.g < 0 && col.b < 0) {
				col = scene->getBackgroundColor();
			}
			fillPixel(j, i, col);
		}
	}
}

Tracer::~Tracer() {
	scene = NULL;
}

// Returns Color(-1,-1,-1) on no intersection
Color Tracer::castRay(Ray ray, int recursions) {
	// find nearest intersecting object
	float minTValue = INFINITY;
	int nearestIndex = -1;
	vector<SceneObject*> sceneObjects = scene->getObjects();
	for (size_t k = 0; k < sceneObjects.size(); k++) {
		float t = sceneObjects[k]->intersection(ray);
		if (t < minTValue) {
			nearestIndex = k;
			minTValue = t;
		}
	}

	if (minTValue == INFINITY) {
		return Color(-1,-1,-1);
	}

	SceneObject *object = sceneObjects[nearestIndex];
	Vec3f intersectPt = ray.origin + ray.direction.scale(minTValue);
	Vec3f norm = object->getNormal(intersectPt);
	Color col = calculateColor(object, norm, ray, minTValue);

	if (recursions >= maxRecursions) {
		return col;
	}

	Color spec = object->getMaterial().getSpecular();
	if (spec.r == 0 && spec.g == 0 && spec.b == 0) {
		return col;
	}

	Ray reflectRay = reflectionRay(ray, norm, minTValue);
	Color reflectColor = castRay(reflectRay, recursions+1);
	if (reflectColor.r < 0 && reflectColor.g < 0 && reflectColor.b < 0) {
		return col;
	}
	Color result = col + (spec * reflectColor);
	result.clamp();
	return result;
}

void Tracer::fillPixel(int row, int col, Color color) {
	color = color.scale(255);
	checkImage[row][col][0] = (GLubyte) color.r;
	checkImage[row][col][1] = (GLubyte) color.g;
	checkImage[row][col][2] = (GLubyte) color.b;
}

void Tracer::setMaxRecursions(int num) {
	maxRecursions = num;
}

Color Tracer:: calculateColor(SceneObject *object, Vec3f norm, Ray ray, float t) {
	Scene *scene = Scene::getInstance();
	vector<Light*> lights = scene->getLights();
	vector<SceneObject*> sceneObjects = scene->getObjects();
	Color sum(0, 0, 0);
	for (size_t k = 0; k < lights.size(); k++) {
		Color Em = lights[k]->getColor();
		Color R = object->getMaterial().getReflected();
		Vec3f dir = lights[k]->getDirection();

		// create shadow ray
		Vec3f shadowOrigin = ray.origin + ray.direction.scale(t);
		Ray shadowRay(shadowOrigin, dir.scale(-1));
		
		// determine if it intersects with any objects
		bool shadow = false;
		for (size_t k = 0; k < sceneObjects.size() && !shadow; k++) {
			float t = sceneObjects[k]->intersection(shadowRay);
			if (t < INFINITY) {
				shadow = true;
			}
		}

		// if not, add light to color sum
		if (!shadow) {
			float cosThetam = clamp(dir.scale(-1).dotProduct(norm));
			sum = sum + (Em*R).scale(cosThetam);
		}
	}
	Color I(object->getMaterial().getAmbient() + sum);
	I.clamp();
	return I;
}

Ray Tracer::reflectionRay(Ray ray, Vec3f n, float t) {
	Vec3f d = ray.direction;
	Vec3f origin = ray.origin + d.scale(t);
	Vec3f direction = d-n.scale(d.dotProduct(n)).scale(2);
	return Ray(origin, direction);
}

float Tracer::clamp(float s) {
	if (s < 0) {
		return 0;
	} else if (s > 1) {
		return 1;
	}
	return s;
}