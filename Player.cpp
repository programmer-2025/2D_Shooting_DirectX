#include "Player.h"
#include "Image.h"
#include "Input.h"
#include "Bullet.h"
#include "ImGUI/imgui.h"

namespace {
	Image* texture = nullptr;
	const float SPEED = 0.1;
}

Player::Player()
	: BaseObject("Player", true) {
	this->point_ = 0;
}

void Player::Init() {
	texture = new Image("player.png", -0.5f, -0.5f);
	texture->Init();
}

void Player::Update() {
	if (texture == nullptr) return;
	auto postion = texture->GetPosition();

	if (Input::IsPushKey(DIK_W)) {
		postion.y += SPEED;
	}
	if (Input::IsPushKey(DIK_S)) {
		postion.y -= SPEED;
	}

	static bool beforeKey = false;
	if (Input::IsPushKey(DIK_SPACE) && !beforeKey) {
		Bullet* bullet = new Bullet();
		bullet->Init();
	}
	beforeKey = Input::IsPushKey(DIK_SPACE);
	

	texture->SetPosition(postion);
}

void Player::Draw(){

}

void Player::Release()
{
}
