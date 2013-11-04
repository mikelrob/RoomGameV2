#ifndef DOOR_H
#define DOOR_H
#include "gameobject.h"

class Door :
	public GameObject
{
public:
	Door(string newName, int newID): GameObject(newName, newID), isLocked(true), isClosed(true) {}
    ~Door();
	Result examine();
	Result use(GameObject& other);
	Result open();
	Result close();

private:
	bool isLocked;
	bool isClosed;
};

#endif