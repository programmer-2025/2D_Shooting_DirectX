#pragma once
#include "BaseObject.h"

class Enemy : public BaseObject {
private:
public:
	Enemy();
	~Enemy();
	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsHit(BaseObject* obj);
};
