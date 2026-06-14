#pragma once
#include "SceneBase.h"

namespace {
    const int GAME_TIME = 15;
}

class RunningScene : public SceneBase {
private:
    float time;
public:
    RunningScene();
    ~RunningScene();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

