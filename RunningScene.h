#pragma once
#include "SceneBase.h"
class RunningScene : public SceneBase {
private:
public:
    RunningScene();
    ~RunningScene();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

