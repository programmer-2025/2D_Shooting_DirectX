#include "BootScene.h"
#include "SceneBase.h"
#include <Windows.h>
#include "DirectX3D.h"
#include "Box2D.h"
#include "Texture.h"
#include "Player.h"
#include "FBX.h"

using namespace DirectX3D;

BootScene::BootScene()
    : SceneBase("BootScene") {
    //new Box2D(-0.5f, 0.5f, 1.0f, -1.0f);
    //new Box2D(-0.7f, 0.5f, 0.1f, -1.0f);
    new Player();
    auto fbx = (new FBX());
    fbx->Load("Oden.fbx");
    assert(DirectX3D::swapChain_);
}

BootScene::~BootScene() {
}

void BootScene::Update() {
    counter_++;
}

void BootScene::Draw() {
}

void BootScene::Init() {
    counter_ = 0;
}

void BootScene::Release() {
}