#include "Enemy.h"
#include "Image.h"
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
}

void Enemy::Update() {
	postion_.y = 2.0f;
	image->SetPosition(postion_);
}

void Enemy::Draw() {
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
	if (distance < 1.0f) {
 		return true;
	}
	return false;
}
