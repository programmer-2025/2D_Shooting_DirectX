#include "RunningScene.h"
#include "Player.h"
#include "FontText.h"
#include "ObjectManager.h"
#include "Enemy.h"

namespace {
	FontText* leftPointText = nullptr;
}

RunningScene::RunningScene()
	: SceneBase("RunningScene") {
}

RunningScene::~RunningScene()
{
}

void RunningScene::Init() {
	new Player();
	new Enemy();

	leftPointText = new FontText(L"現在の得点", DirectX::XMFLOAT3(-350, -220, 0));
}

void RunningScene::Update() {
	Player* player = ObjectManager::GetDrawObject<Player>();
	if (player != nullptr) {
		leftPointText->SetText(L"現在の得点：" + std::to_wstring(player->GetPoint()));
	}
	
}

void RunningScene::Draw()
{
}

void RunningScene::Release()
{
}
