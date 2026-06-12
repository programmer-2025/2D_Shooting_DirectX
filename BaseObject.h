#pragma once
#include <string>
#include <DirectXMath.h>

class BaseObject {
private:
protected:
    std::string name_;
    bool isAlive_;
    bool isShowing_;

    DirectX::XMFLOAT3 postion_;
	DirectX::XMFLOAT3 rotation_;
	DirectX::XMFLOAT3 scale_;
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Release() = 0;

    BaseObject(std::string name, bool isAlive);
    virtual ~BaseObject() {}

    std::string GetName() { return name_; };
    bool IsAlive() { return isAlive_; };
    void KillMe() { this->isAlive_ = false; }
    bool IsShowing() { return isShowing_; }
    void SetShowing(const bool flag) { this->isShowing_ = flag; }

	DirectX::XMFLOAT3 GetPosition() const { return postion_; }
	void SetPosition(const DirectX::XMFLOAT3 position) { this->postion_ = position; }
	DirectX::XMFLOAT3 GetRotation() const { return rotation_; }
	void SetRotation(const DirectX::XMFLOAT3 rotation) { this->rotation_ = rotation; }
	DirectX::XMFLOAT3 GetScale() const { return scale_; }
	void SetScale(const DirectX::XMFLOAT3 scale) { this->scale_ = scale; }


};