#include "BootScene.h"
#include "SceneBase.h"
#include <Windows.h>
#include "DirectX3D.h"
#include "Box2D.h"
#include "Texture.h"
#include "Player.h"
#include "FBX.h"
#include "ImGUI/imgui.h"
#include "Camera.h"
#include "FontText.h"
#include "SceneManager.h"
#include "DirectX2D.h"

using namespace DirectX3D;
using namespace DirectX;

BootScene::BootScene()
    : SceneBase("BootScene") {
    assert(DirectX3D::swapChain_);
    DirectX2D::Init();
}

BootScene::~BootScene() {
}

void BootScene::Update() {
    counter_++;
    SceneManager::ChangeScene("TitleScene");
}

void BootScene::Draw() {
    Camera* currentCamera = CameraManager::getCurentCamera();
    DirectX::XMFLOAT3 cameraPos = currentCamera->getCameraPostion();
    DirectX::XMFLOAT3 targetPos = currentCamera->getFoucsPostion();

    ImGui::Begin("BootScene");
	ImGui::Text("Camera Name: %s", currentCamera->getName().c_str());
    ImGui::SliderFloat("cameraPosX", &cameraPos.x, -20.0f, 20.0f);
	ImGui::SliderFloat("cameraPosY", &cameraPos.y, -20.0f, 20.0f);
	ImGui::SliderFloat("cameraPosZ", &cameraPos.z, -20.0f, 20.0f);
	ImGui::SliderFloat("targetPosX", &targetPos.x, -20.0f, 20.0f);
	ImGui::SliderFloat("targetPosY", &targetPos.y, -20.0f, 20.0f);
	ImGui::SliderFloat("targetPosZ", &targetPos.z, -20.0f, 20.0f);
    ImGui::End();

	currentCamera->setCameraPostion(cameraPos);
	currentCamera->setFoucsPostion(targetPos);
}

void BootScene::Init() {
    counter_ = 0;
	CameraManager::addCamera("rootCamera");
    CameraManager::setCurentCamera("rootCamera");
}

void BootScene::Release() {
}