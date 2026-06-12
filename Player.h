#pragma once
#include "BaseObject.h"

class Player : public BaseObject {
private:
	int point_;
public:
	Player();
	~Player() {};
	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	int GetPoint() { return point_; }
	void SetPoint(int point) { this->point_ = point; }
};
