#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<string>
#include<iostream>
using std::string;
using std::cout;

enum Result { NOERR, DOOR, BOX, UNLOCKED};

class GameObject
{
public:
	GameObject(string newName, int newID);
	virtual ~GameObject();
	//possible actions with game objects
	virtual Result examine() = 0;			//use pure virtual func as there is no default string
	virtual Result use(GameObject& other);
	virtual Result open();
	virtual Result close();
	virtual Result turnOn();
	virtual Result turnOff();

	//accessor functions
	int getID(){return ID;}
	virtual string getName(){return name;}
	string getScanName(){return scanName;}

protected:
	int ID;
	string name;

private:
	GameObject();				//default constructor is made private and so rendered unusable
	string scanName;



};

#endif