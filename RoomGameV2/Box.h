#ifndef BOX_H
#define BOX_H
#include "gameobject.h"

class Box :
	public GameObject
{
public:
	Box(string newName, int newID):GameObject(newName, newID), isOpen(false) {}
	~Box();
	Result examine();
	Result open();
	Result close();

private:
	bool isOpen;
};

#endif