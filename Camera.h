#pragma once
#include <DirectXMath.h>

class Camera {
private:
	DirectX::XMFLOAT3 cameraPostion_;
	DirectX::XMFLOAT3 foucusPostion_;
	DirectX::XMFLOAT3 upDirection_;
public:

	Camera() {
		cameraPostion_ = { 0.0f, 0.0f, -5.0f};
		foucusPostion_ = { 0.0f, 2.0f, 0.0f };
		upDirection_ = { 0.0f, 1.0f, 0.0f };
	}

	Camera(DirectX::XMFLOAT3 cameraPos, DirectX::XMFLOAT3 foucusPos) {
		this->cameraPostion_ = cameraPos;
		this->foucusPostion_ = foucusPos;
	}

	inline DirectX::XMMATRIX getMatrix() {
		return DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(cameraPostion_.x, cameraPostion_.y, cameraPostion_.z, 1.0f),
			DirectX::XMVectorSet(foucusPostion_.x, foucusPostion_.y, foucusPostion_.z, 1.0f),
			DirectX::XMVectorSet(upDirection_.x, upDirection_.y, upDirection_.z, 1.0f)
		);
	}

	inline DirectX::XMFLOAT3 getCameraPostion() {
		return cameraPostion_;
	}

	inline void setCameraPostion(DirectX::XMFLOAT3 cameraPos) {
		this->cameraPostion_ = cameraPos;
	}

	inline DirectX::XMFLOAT3 getFoucsPostion() {
		return foucusPostion_;
	}

	inline void setFoucsPostion(DirectX::XMFLOAT3 foucsPos) {
		this->foucusPostion_ = foucsPos;
	}
};

namespace CameraManager {
	void setCurentCamera(Camera* camera);
	Camera* getCurentCamera();
}

