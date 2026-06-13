#include "Player.h"
#include "Image.h"
#include "Input.h"
#include "Bullet.h"
#include "ImGUI/imgui.h"
#include "ObjectManager.h"
#include "Enemy.h"
using namespace DirectX;

namespace {
	Image* texture = nullptr;
	const float SPEED = 1.0f;
}

Player::Player()
	: BaseObject("Player", true) {
	this->point_ = 0;
}

void Player::Init() {
	texture = new Image("player.png", 64, 64);
	texture->Init();
	postion_ = texture->GetPosition();
	rotation_ = texture->GetRotation();
	scale_ = texture->GetScale();
}

void Player::Update() {
	if (texture == nullptr) return;

	if (Input::IsPushKey(DIK_A)) {
		postion_.x -= SPEED;
	}
	if (Input::IsPushKey(DIK_D)) {
		postion_.x += SPEED;
	}
	if (Input::IsPushKey(DIK_W)) {
		postion_.y -= SPEED;
	}
	if (Input::IsPushKey(DIK_S)) {
		postion_.y += SPEED;
	}

	if (Input::IsPushKey(DIK_LEFT)) {
		rotation_.z += SPEED;
	}
	if (Input::IsPushKey(DIK_RIGHT)) {
		rotation_.z -= SPEED;
	}

	static bool beforeKey = false;
	if (Input::IsPushKey(DIK_SPACE) && !beforeKey) {
		Bullet* bullet = new Bullet(this);
		bullet->Init();
		bullet->SetPosition(postion_);
	}
	beforeKey = Input::IsPushKey(DIK_SPACE);
	

	texture->SetPosition(postion_);
	texture->SetRotation(rotation_);
	texture->SetScale(scale_);
}

void Player::Draw(){
	Enemy* enemy = ObjectManager::GetDrawObject<Enemy>();
	auto objLoc = enemy->GetPosition();
	XMVECTOR bVec = XMVectorSet(objLoc.x, objLoc.y, objLoc.z, 1.0f);
	auto obj1Loc = postion_;
	XMVECTOR aVec = XMVectorSet(obj1Loc.x, obj1Loc.y, obj1Loc.z, 1.0f);

	XMVECTOR length = XMVectorSubtract(bVec, aVec);
	float distance = XMVectorGetX(XMVector3Length(length));

#ifdef _DEBUG
	ImGui::Begin("Player");
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

void Player::Release()
{
}
