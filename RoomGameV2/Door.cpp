#include "Door.h"
#include "DoorKey.h"
#include <typeinfo>

Door::~Door(){}

Result Door::examine(){
	if(isLocked)
		cout << "\nThis is the only door out of the room. It appears to be locked.";
	else
		cout << "\nThis is the only door out of the room. It is unlocked.";
	return NOERR;
}

Result Door::use(GameObject& other){
	if(typeid(other) == typeid(DoorKey)){				//if ither item is a door key
		if(static_cast<DoorKey&>(other).isItVisible()){	//and if door key is visible
			if(ID == other.getID()){ 	//if key fits lock
				if(isLocked){
					isLocked = false;
					cout << "\nYou have just unlocked the door.";
					return UNLOCKED;
				}else
					cout << "\nThe door is already unlocked.";
			}else
				cout << "\nThis is not the key for this door.";
		}else
			cout << "\nUnknown object.";
	}else
		GameObject::use(other);				//call function from parent class
	return NOERR;
}

Result Door::open(){
	if(isClosed){
		if(isLocked)
			cout << "\nDoor cannot be opened. It is locked.";
		else{
			isClosed = false;		//unnecesary methinks but ....
			cout << "\nCongratulations, you have escaped from the room.";
			return DOOR;
		}
	}else
		cout << "\nThe door is already open.";
	return NOERR;
}

Result Door::close(){
	if(isClosed)
		cout << "\nThe door is already closed.";
	else{								//else not required since open door exits game
		isClosed = true;
		cout << "\nThe door is now closed.";
		return DOOR;
	}
	return NOERR;
}
