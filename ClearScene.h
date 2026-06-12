#pragma once
#include "SceneBase.h"
class ClearScene : public SceneBase {
private:
public:
    ClearScene();
    ~ClearScene();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

