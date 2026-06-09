#include "Camera.h"

namespace CameraManager{
	inline Camera* currentCamera_ = nullptr;

	void setCurentCamera(Camera* camera) {
		currentCamera_ = camera;
	}

	Camera* getCurentCamera() {
		if (currentCamera_ == nullptr) {
			setCurentCamera(new Camera());
		}
		return currentCamera_;
	}
}