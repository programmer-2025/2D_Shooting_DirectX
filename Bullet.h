#pragma once
#include "BaseObject.h"
#include "Image.h"

class Bullet : public BaseObject {
private:
	BaseObject* parentBullet = nullptr;
	Image* image = nullptr;
public:
	Bullet(BaseObject* parent);
	~Bullet();
	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
