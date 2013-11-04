#include "Box.h"

Box::~Box(void){}

Result Box::examine(){
	if(isOpen){
		cout << "\nThere is a door key inside.";
	}else{
		cout << "\nThere appears to be something inside the box.";
	}
	return NOERR;
}
Result Box::open(){
	if(isOpen){
		cout << "\nThe box is already open.";
		return NOERR;
	}else{
		isOpen = true;
		cout << "\nThe box is now open.";
		return BOX;
	}
}

Result Box::close(){
	if(isOpen){
		isOpen = false;
		cout << "\nThe box is now closed.";
		return BOX;
	}else{
		cout << "\nThe box is already closed.";
	}
	return NOERR;
}