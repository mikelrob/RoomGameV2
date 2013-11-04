#include "DoorKey.h"

DoorKey::~DoorKey(void)
{
}

Result DoorKey::examine(){
	if(isVisible){
		cout << "\nThis appears to be the key for the door.";
	}else{
		cout << "\nUnknown object."; 
	}
	return NOERR;
}

Result DoorKey::use(GameObject& other){
		return other.use(*this);		//call function already coded. Saves access worries too
}

string DoorKey::getName(){
	if(isVisible)
		return name;
	else
		return "invisible";
}