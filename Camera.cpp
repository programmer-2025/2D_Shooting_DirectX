#include "Camera.h"
#include <map>
#include <string>

namespace CameraManager{
	inline std::map<std::string, Camera*> cameraMap;
	inline Camera* currentCamera_ = nullptr;

	void addCamera(std::string name, Camera* camera) {
		cameraMap[name] = camera;
	}

	void setCurentCamera(std::string name) {
		if (cameraMap.find(name) != cameraMap.end()) { 
			currentCamera_ = cameraMap[name];
		}
	}

	Camera* getCamera(std::string name) {
		return cameraMap[name];
	}

	Camera* getCurentCamera() {
		return currentCamera_;
	}
}