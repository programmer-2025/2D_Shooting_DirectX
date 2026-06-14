#include "Enemy.h"
#include "Image.h"
#include "ImGUI/imgui.h"
#include "framework.h"
using namespace DirectX;

namespace {
	Image* image = nullptr;
}

Enemy::Enemy()
	: BaseObject("Enemy", true) {
}

Enemy::~Enemy() {
}


void Enemy::Init() {
	image = new Image("Enemy.png", 64, 64);
	image->Init();
	postion_ = image->GetPosition();
	postion_ = {Screen::WIDTH / 2, 10, 0};
	rotation_ = image->GetRotation();
	scale_ = image->GetScale();
	velocity_ = { 0, 1.0f, 0 };
}

void Enemy::Update() {
	if (-64 <= postion_.x && postion_.x <= Screen::WIDTH &&
		-64 <= postion_.y && postion_.y <= Screen::HEIGHT) {

	}
	else {
		postion_.y = -64;
	}

	postion_.y += velocity_.y;

	image->SetPosition(postion_);
	image->SetRotation(rotation_);
	image->SetScale(scale_);
}

void Enemy::Draw() {
#ifdef _DEBUG
	ImGui::Begin("Enemy");
	ImGui::SliderFloat("X", &postion_.x, -1.0f, 1280.0f);
	ImGui::SliderFloat("Y", &postion_.y, -1.0f, 720.0f);
	ImGui::SliderFloat("Z", &postion_.z, -1.0f, 10.0f);
	ImGui::SliderFloat("angleX", &rotation_.x, -1.0f, 1.0f);
	ImGui::SliderFloat("angleY", &rotation_.y, -1.0f, 1.0f);
	ImGui::SliderFloat("angleZ", &rotation_.z, -1.0f, 1.0f);
	ImGui::SliderFloat("scaleX", &scale_.x, 0.5f, 10.0f);
	ImGui::SliderFloat("scaleY", &scale_.y, 0.5f, 10.0f);
	ImGui::SliderFloat("scaleZ", &scale_.z, 0.5f, 10.0f);
	ImGui::End();
#endif
}

void Enemy::Release() {
}

bool Enemy::IsHit(BaseObject* obj) {
	auto objLoc = obj->GetPosition();
	XMVECTOR bVec = XMVectorSet(objLoc.x, objLoc.y, objLoc.z, 1.0f);
	auto obj1Loc = GetPosition();
	XMVECTOR aVec = XMVectorSet(obj1Loc.x, obj1Loc.y, obj1Loc.z, 1.0f);

	XMVECTOR subtract = XMVectorSubtract(bVec, aVec);
	XMVECTOR length = XMVector3Length(subtract);
	float distance = XMVectorGetX(length);
	if (distance < 32.0f + 32.0f) {
 		return true;
	}
	return false;
}
