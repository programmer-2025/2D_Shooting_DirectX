#include "Bullet.h"
#include "Image.h"
#include "Input.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "Player.h"

namespace {
	Image* texture = nullptr;
	const float SPEED = 0.1;
}

Bullet::Bullet(BaseObject* parent)
	: BaseObject("Bullet", true) {
	this->parentBullet = parent;
}

Bullet::~Bullet() {
	if (texture != nullptr) {
		texture->KillMe();
	}
}

void Bullet::Init() {
	texture = new Image("Bullet.png", -0.5f, -0.5f);
	texture->Init();
	postion_ = texture->GetPosition();
	rotation_ = texture->GetRotation();
}

void Bullet::Update() {
	if (texture == nullptr) return;
	postion_.y += SPEED;

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
