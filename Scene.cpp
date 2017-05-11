#include "Scene.h"
#include <iostream>
using namespace std;


// Singleton Scene class
bool Scene::instanceFlag = false;
Scene* Scene::scene = NULL;

Scene* Scene::getInstance() {
	if (!instanceFlag) {
		scene = new Scene();
		instanceFlag = true;
		return scene;
	}
	return scene;
}

Scene::~Scene() {
	instanceFlag = false;
	scene = NULL;

	delete camera;
	camera = NULL;
	clearObjects();
	clearLights();
}

void Scene::setCamera(Camera *camera) {
	if (this->camera != NULL) {
		delete this->camera;
	}
	this->camera = camera;
}

void Scene::addObject(SceneObject *object) {
	sceneObjects.push_back(object);
}

void Scene::addLight(Light *light) {
	lights.push_back(light);
}

void Scene::setBackgroundColor(Color color) {
	backgroundColor = color;
}

Camera* Scene::getCamera() const {
	return camera;
}

vector<SceneObject*> Scene::getObjects() const {
	return sceneObjects;
}

vector<Light*> Scene::getLights() const {
	return lights;
}

Color Scene::getBackgroundColor() const {
	return backgroundColor;
}

void Scene::printObjects() const {
	for (size_t i = 0; i < sceneObjects.size(); i++) {
		cout << "Object #" << i+1 << endl;
		sceneObjects[i]->print();
		cout << endl;
	}
}

void Scene::printLights() const {
	for (size_t i = 0; i < lights.size(); i++) {
		cout << "Light #" << i + 1 << ":" << endl;
		lights[i]->print();
	}
}

void Scene::clearObjects() {
	for (size_t i = 0; i < sceneObjects.size(); i++) {
		delete sceneObjects[i];
		sceneObjects[i] = NULL;
	}
	sceneObjects.clear();
}

void Scene::clearLights() {
	for (size_t i = 0; i < lights.size(); i++) {
		delete lights[i];
		lights[i] = NULL;
	}
	lights.clear();
}