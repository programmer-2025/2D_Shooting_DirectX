#pragma once
#include "SceneBase.h"
#include <DirectXMath.h>

struct ConstantBuffer {
    DirectX::XMMATRIX worldViewProj;
};

class BootScene : public SceneBase {
private:
    int counter_;
public:
    BootScene();
    ~BootScene();
    void Update() override;
    void Draw() override;
    void Init() override;
    void Release() override;
};

