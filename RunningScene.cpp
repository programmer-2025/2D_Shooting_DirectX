#include "RunningScene.h"
#include "Player.h"

RunningScene::RunningScene()
	: SceneBase("RunningScene") {
}

RunningScene::~RunningScene()
{
}

void RunningScene::Init() {
	new Player();
}

void RunningScene::Update()
{
}

void RunningScene::Draw()
{
}

void RunningScene::Release()
{
}
