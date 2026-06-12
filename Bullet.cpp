#include "Bullet.h"
#include "Image.h"
#include "Input.h"

namespace {
	Image* texture = nullptr;
	const float SPEED = 0.1;
}

Bullet::Bullet()
	: BaseObject("Bullet", true) {
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

	texture->SetPosition(postion_);
}

void Bullet::Draw() {

}

void Bullet::Release()
{
}
