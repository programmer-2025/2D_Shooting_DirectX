#include "Bullet.h"
#include "Image.h"
#include "Input.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "Player.h"
#include "framework.h"
#include "ImGUI/imgui.h"

namespace {
	const float SPEED = 1.0;
}

Bullet::Bullet(BaseObject* parent)
	: BaseObject("Bullet", true) {
	this->parentBullet = parent;
	this->velocity_ = { 0, -1, 0 };
}

Bullet::~Bullet() {
	if (image != nullptr) {
		image->KillMe();
	}
}

void Bullet::Init() {
	image = new Image("Bullet.png", 64, 64);
	image->Init();
	postion_ = image->GetPosition();
	rotation_ = image->GetRotation();
	scale_ = image->GetScale();
}

void Bullet::Update() {
	if (image == nullptr) return;
	postion_.y += velocity_.y;

	if (-64 <= postion_.x && postion_.x <= Screen::WIDTH &&
			-64 <= postion_.y && postion_.y <= Screen::HEIGHT) {

	}
	else {
		KillMe();
	}

	Enemy* enemy = ObjectManager::GetDrawObject<Enemy>();
	if (enemy->IsHit(this)) {
		KillMe();
		Player* player = dynamic_cast<Player*>(parentBullet);
		if (player != nullptr) {
			player->SetPoint(player->GetPoint() + 1.0f);
		}
	}

	image->SetPosition(postion_);
	image->SetRotation(rotation_);
	image->SetScale(scale_);
}

void Bullet::Draw() {
#ifdef _DEBUG
	ImGui::Begin("Bullet");
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

void Bullet::Release()
{
}
