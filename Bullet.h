#pragma once
#include "BaseObject.h"

class Bullet : public BaseObject {
private:
public:
	Bullet();
	~Bullet() {};
	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
