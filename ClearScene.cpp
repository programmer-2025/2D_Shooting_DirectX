#include "ClearScene.h"
#include "FontText.h"
#include "framework.h"
#include "SceneManager.h"

namespace {
	FontText* leftPointText = nullptr;
	float count = 0;
}

ClearScene::ClearScene()
	: SceneBase("ClearScene") {
}

ClearScene::~ClearScene()
{
}

void ClearScene::Init()
{
	new FontText(L"ゲーム終了!");
}

void ClearScene::Update() {
	count += GameFramework::GetDeltaTime();
	if (count > 10) {
		SceneManager::ChangeScene("TitleScene");
	}
}

void ClearScene::Draw()
{
}

void ClearScene::Release()
{
}
