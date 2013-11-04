#include "Television.h"

Television::~Television(){}

Result Television::examine(){
	if(isOn){
		cout << "\nThe television is showing a cartoon rerun.";
	}else{
		cout << "\nThe television seems to be off.";
	}
	return NOERR;
}

Result Television::turnOn(){
	if(isOn){
		cout << "\nThe television is already on.";
	}else{
		isOn = true;
		cout << "\nYou have turned the television on.";
	}
	return NOERR;
}

Result Television::turnOff(){
	if(isOn){
		isOn = false;
		cout << "\nYou have turned the television off.";
	}else{
		cout << "\nThe television is already off.";
	}
	return NOERR;
}