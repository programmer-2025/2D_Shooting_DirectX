#pragma once
#include <string>

class BaseObject {
private:
protected:
    std::string name_;
    bool isAlive_;
    bool isShowing_;
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Release() = 0;

    BaseObject(std::string name, bool isAlive);
    virtual ~BaseObject() {}

    std::string GetName() { return name_; };
    bool IsAlive() { return isAlive_; };
    void KillMe() { this->isAlive_ = true; }
    bool IsShowing() { return isShowing_; }
    void SetShowing(const bool flag) { this->isShowing_ = flag; }
};