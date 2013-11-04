#pragma once
#include "gameobject.h"

class DoorKey :
	public GameObject
{
public:
	DoorKey(string newName, int newID): GameObject(newName, newID), isVisible(false) {}
	~DoorKey();
	Result examine();
	Result use(GameObject& other);

	//accessor functions
	virtual string getName();
	bool isItVisible(){return isVisible;}		//is this too confusing with the data member?

	//mutator functions
	void setVisibility(bool isVis){isVisible = isVis;}

private:
	bool isVisible;								//is this too onfusing with the memebr function?

};
