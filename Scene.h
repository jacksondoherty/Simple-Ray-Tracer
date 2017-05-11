#ifndef SCENE_H
#define SCENE_H

#include "SceneObject.h"
#include <vector>
#include "Light.h"
#include "Camera.h"
#include "Color.h"
#include <cstddef>
using namespace std;


// Singleton Scene class
class Scene {
	private:
		static bool instanceFlag;
		static Scene *scene;
		Scene(): camera(NULL) {}
		Camera *camera;
		vector<SceneObject*> sceneObjects;
		vector<Light*> lights;
		Color backgroundColor;
	public:
		static Scene* getInstance();
		~Scene();
		void setCamera(Camera *camera);
		void addObject(SceneObject *object);
		void addLight(Light *light);
		void setBackgroundColor(Color color);
		Camera* getCamera() const;
		vector<SceneObject*> getObjects() const;
		vector<Light*> getLights() const;
		Color getBackgroundColor() const;
		void printObjects() const;
		void printLights() const;
		void clearObjects();
		void clearLights();
};

#endif /* SCENE_H */