#include "Bullet.h"
#include "Image.h"
#include "Input.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "Player.h"
#include "framework.h"

namespace {
	Image* texture = nullptr;
	const float SPEED = 1.0;
}

Bullet::Bullet(BaseObject* parent)
	: BaseObject("Bullet", true) {
	this->parentBullet = parent;
	this->velocity_ = { 0, -1, 0 };
}

Bullet::~Bullet() {
	if (texture != nullptr) {
		texture->KillMe();
	}
}

void Bullet::Init() {
	texture = new Image("Bullet.png", 64, 64);
	texture->Init();
	postion_ = texture->GetPosition();
	rotation_ = texture->GetRotation();
}

void Bullet::Update() {
	if (texture == nullptr) return;
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

	texture->SetPosition(postion_);
}

void Bullet::Draw() {

}

void Bullet::Release()
{
}
