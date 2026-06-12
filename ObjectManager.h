#pragma once
#include <vector>
#include "BaseObject.h"

namespace ObjectManager {
    inline std::vector<BaseObject*> objList;

    void InitManager();
    void AddObject(BaseObject* obj);
    void RemoveObject(BaseObject* obj);
    void ClearObject();
    void UpdateManager();

    template<class T> T* GetDrawObject() {
        for (BaseObject* obj : objList) {
            if (obj == nullptr) continue;
            T* instance = dynamic_cast<T*>(obj);
            if (instance != nullptr) {
                return instance;
            }
        }
        return nullptr;
    }
}