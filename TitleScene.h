#pragma once
#include "SceneBase.h"
class TitleScene :  public SceneBase {
private:
public:
    TitleScene();
    ~TitleScene();
    void Update() override;
    void Draw() override;
    void Init() override;
    void Release() override;
};

