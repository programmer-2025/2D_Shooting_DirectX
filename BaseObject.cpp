#include "BaseObject.h"
#include "ObjectManager.h"

BaseObject::BaseObject(std::string name, bool isAlive) {
	name_ = name;
	isAlive_ = isAlive;
	isShowing_ = true;
	ObjectManager::AddObject(this);
}
