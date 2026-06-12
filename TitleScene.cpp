#include "TitleScene.h"
#include "Input.h"
#include "SceneManager.h"
#include "FontText.h"

TitleScene::TitleScene()
	: SceneBase("TitleScene") {
	new FontText(L"Please Space Key!");
}

TitleScene::~TitleScene() {
}

void TitleScene::Update() {
	if (Input::IsPushKey(DIK_SPACE)) {
		SceneManager::ChangeScene("RunningScene");
	}
}

void TitleScene::Draw() {
}

void TitleScene::Init() {
}

void TitleScene::Release()
{
}
