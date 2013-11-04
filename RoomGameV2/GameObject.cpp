#include "GameObject.h"
#include<iostream>
#include<cctype>
using std::cout;

GameObject::GameObject(string newName, int newID):name(newName), ID(newID){
	int length = name.length();
	scanName = string(length, ' ');		//initialise string
	for(int i = 0 ; i < length ; i++)
		scanName[i] = std::tolower(name[i]);
}

GameObject::~GameObject(){}

Result GameObject::use(GameObject &other){
	cout << "\nThis object cannot be used with " + other.name + ".";
	return NOERR;
}

Result GameObject::open(){
	cout << "\nThis object cannot be opened.";
	return NOERR;
}

Result GameObject::close(){
	cout << "\nThis object cannot be closed.";
	return NOERR;
}

Result GameObject::turnOn(){
	cout << "\nThis object cannot be turned on.";
	return NOERR;
}

Result GameObject::turnOff(){
	cout << "\nThis object cannot be turned off.";
	return NOERR;
}