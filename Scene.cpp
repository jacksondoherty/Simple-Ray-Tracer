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
	int i = 1;
	for (auto it = sceneObjects.begin(); it != sceneObjects.end() ; ++it, i++) {
		cout << "Object #" << i << endl;
		(*it)->print();
		cout << endl;
	}
}

void Scene::printLights() const {
	int i = 1;
	for (auto it = lights.begin(); it != lights.end() ; ++it, i++) {
		cout << "Light #" << i << ":" << endl;
		(*it)->print();
	}
}

void Scene::clearObjects() {
	for (auto it = sceneObjects.begin(); it != sceneObjects.end() ; ++it) {
		delete *it;
		*it = NULL;
	}
	sceneObjects.clear();
}

void Scene::clearLights() {
	for (auto it = lights.begin(); it != lights.end() ; ++it) {
		delete *it;
		*it = NULL;
	}
	lights.clear();
}