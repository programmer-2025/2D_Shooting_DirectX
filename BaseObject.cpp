#include "BaseObject.h"
#include "ObjectManager.h"

BaseObject::BaseObject(std::string name, bool isAlive) {
	name_ = name;
	isAlive_ = isAlive;
	isShowing_ = true;
	postion_ = { 0.0f, 0.0f, 0.0f };
	velocity_ = { 0.0f, 0.0f, 0.0f };
	rotation_ = { 0.0f, 0.0f, 0.0f };
	scale_ = { 1.0f, 1.0f, 1.0f };
	ObjectManager::AddObject(this);
}
