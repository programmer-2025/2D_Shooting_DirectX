#include "RunningScene.h"
#include "Player.h"
#include "FontText.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "framework.h"
#include "SceneManager.h"
#include "FBX.h"

namespace {
	FontText* leftPointText = nullptr;
	FontText* rightTimeText = nullptr;
}

RunningScene::RunningScene()
	: SceneBase("RunningScene") {
	time = GAME_TIME;
}

RunningScene::~RunningScene()
{
}

void RunningScene::Init() {
	new Player();
	new Enemy();
	FBX* fbx = new FBX();
	fbx->Load("Oden.fbx");

	leftPointText = new FontText(L"現在の得点", DirectX::XMFLOAT3(-350, -220, 0));
	rightTimeText = new FontText(L"残り時間：", DirectX::XMFLOAT3(350, -220, 0));
}

void RunningScene::Update() {
	time -= GameFramework::GetDeltaTime();

	Player* player = ObjectManager::GetDrawObject<Player>();
	if (player != nullptr) {
		leftPointText->SetText(L"現在の得点：" + std::to_wstring(player->GetPoint()));
		rightTimeText->SetText(L"残り時間：" + std::to_wstring(time));
	}
	
	if (time < 0) {
		SceneManager::ChangeScene("ClearScene");
		time = GAME_TIME;
	}
}

void RunningScene::Draw()
{
}

void RunningScene::Release() {

}
