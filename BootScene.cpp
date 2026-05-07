#include "BootScene.h"
#include "SceneBase.h"
#include <Windows.h>
#include "DirectX3D.h"
#include "Box2D.h"
#include "Texture.h"

namespace {
    Box2D* box = nullptr;
    Box2D* box2 = nullptr;
	Texture* texture = nullptr;
}

using namespace DirectX3D;

BootScene::BootScene()
    : SceneBase("BootScene") {
    box = new Box2D(-0.5f, 0.5f, 1.0f, -1.0f);
    box2 = new Box2D(-0.7f, 0.5f, 0.1f, -1.0f);
	texture = new Texture("texture.png", -0.5f, -0.5f);
    box->Init();
    box2->Init();
    texture->Init();
}

BootScene::~BootScene() {
}

void BootScene::Update() {
    counter_++;
	texture->Update();
}

void BootScene::Draw() {
    //box->Draw();
    //box2->Draw();
	texture->Draw();
}

void BootScene::Init() {
    counter_ = 0;
}

void BootScene::Release() {
}