#ifndef TELEVISION_H
#define TELEVISION_H
#include "gameobject.h"

class Television :
	public GameObject
{
public:
	Television(string newName, int newID):GameObject(newName, newID), isOn(false) {}
	~Television();
	Result examine();
	Result turnOn();
	Result turnOff();

private:
	bool isOn;

};

#endif