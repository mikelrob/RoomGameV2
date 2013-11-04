#include "GameObject.h"
#include "Door.h"
#include "DoorKey.h"
#include "Television.h"
#include "Box.h"

#include<cctype>
#include<string>
#include<iostream>
using std::string;
using std::cout;
using std::cin;

//function prototypes
int pickFromList(const string criteria, const string* list, const int listSize);
void listRoomItems(GameObject* thisRoom[], int roomSize);
void printScreenBreak();

int main(){
	//initialise game
	const string separators = " ";
	const int numObjects = 4;
	const int maxInput = 5;				//maximum number of words the user must input for longest command
	const string commandList[] = { "list", "examine", "use", "turn on", "turn off", "open", "close"};
	const string invalidCommand = "\nInvalid Command!";
	const string unknownObject = "\nUnknown Object.";
	enum { NOCOMMAND = -1, LIST, EXAMINE, USE, TURNON, TURNOFF, OPEN, CLOSE };	//anonymous enum for commandID

	int command = 0;					//commandID of selected command
	int object1 = 0, object2 = 0;		//objectID of selected objects 

	string commandLine  = "";
	string userInput[maxInput] = {};
	bool isComplete = false;

	GameObject* apRoomContents[numObjects];
	apRoomContents[0] = new Door("Door", 1);
	apRoomContents[1] = new DoorKey("Door Key", 1);
	apRoomContents[2] = new Television("Television", 0);
	apRoomContents[3] = new Box("Box", 0);

	//start
	string objectList[numObjects];
	for(int i = 0 ; i < numObjects ; i++)
		objectList[i] = apRoomContents[i]->getScanName();

	cout << "\nYou are in a room with various objects. There is a door across the way."
		 << "\nWhat are you going to do?\n";

	while(!isComplete){
		cout << "\nlist\t\t- Display the objects in the room"
			 << "\nexamine x\t- Examines the specified object"
			 << "\nuse x with y\t- Uses the specified object with the other"
			 << "\nturn on x\t- Turns on specified object"
			 << "\nturn off x\t- Turns off specified object"
			 << "\nopen x\t\t- Opens the specified object"
			 << "\nclose x\t\t- Closes the specified object"
			 << "\n\nEnter command:\n>";

		std::getline(cin, commandLine);		//store user input in command line

		//change whole command line to lower case
		for(unsigned int i = 0 ; i < commandLine.length() ; i++)
			commandLine[i] = std::tolower(commandLine[i]);

		//clear out last user input from array
		for(int i = 0 ; i < maxInput ; i++)
			userInput[i] = "";

		//break down commandLine into maximum 'maxInput' phrases
		size_t start = 0;
		size_t end = commandLine.find_first_of(separators);

		for(int i = 0 ; i < maxInput && start != string::npos ; i++){	//for the rest of the userInput array and while not end of string
			end = commandLine.find_first_of(separators, start);			//find end of word
			if(end == string::npos)										//if is end of string
				end = commandLine.length();								//make end the last char
			userInput[i] = commandLine.substr(start, end - start);	//store the word in the userInput array
			start = commandLine.find_first_not_of(separators, end);	//find the start of the next word after end
		}

		//analyse the user input
		if(userInput[0].compare("turn") == 0			//if first word is turn
			&& (userInput[1].compare("on") == 0			//and (second word is on
				|| userInput[1].compare("off") == 0)){	//     or off)

				userInput[0] += " " + userInput[1];		//then concatenate on or off onto userinput[0] NB parenthesis not req due to associativity on operators
				for(int i = 2 ; i < maxInput ; i++)
					userInput[i-1] = userInput[i];		//and shift all words down the array
		}
		if(userInput[1].compare("door") == 0 && userInput[2].compare("key") == 0){
			userInput[1] += " " + userInput[2];			//concatenate key onto door
			for(int i = 3 ; i < maxInput ; i++)
				userInput[i-1] = userInput[i];		//and shift all words down the array
			userInput[4] = "";						//clear duplicate elment
		}else if(userInput[3].compare("door") == 0 && userInput[4].compare("key") == 0){
			userInput[3] += " " + userInput[4];			//concatenate key onto door
			userInput[4] = "";							//clear duplicate elment
		}
		//all required words are now stored in the userInput array

		command = pickFromList(userInput[0], commandList, sizeof commandList/sizeof commandList[0]);
		object1 = pickFromList(userInput[1], objectList, numObjects);
		object2 = pickFromList(userInput[3], objectList, numObjects);
		
		printScreenBreak();
		//select appropriate output to user
		switch(command){
			case NOCOMMAND:
				cout << invalidCommand;
				break;
			///////////////////////////////////////////////////////////////////
			case LIST:
				listRoomItems(apRoomContents, numObjects);
				break;
			///////////////////////////////////////////////////////////////////
			case EXAMINE:
				if(object1 >= 0)							//if object code is positive (ie on the list)
					apRoomContents[object1]->examine();
				else
					cout << unknownObject;
				break;
			///////////////////////////////////////////////////////////////////
			case USE:
				if(userInput[2].compare("with") == 0)
					if(object1 >= 0 && object2 >= 0)
						apRoomContents[object1]->use(*apRoomContents[object2]);
					else
						cout << unknownObject;
				else
					cout << invalidCommand;
				break;
			//////////////////////////////////////////////////////////////////
			case TURNON:
				if(object1 >= 0)
					apRoomContents[object1]->turnOn();
				else
					cout << unknownObject;
				break;
			//////////////////////////////////////////////////////////////////
			case TURNOFF:
				if(object1 >= 0)
					apRoomContents[object1]->turnOff();
				else
					cout << unknownObject;
				break;
			//////////////////////////////////////////////////////////////////
			case OPEN:
				if(object1 >= 0){
					int DOORKEY = pickFromList("door key", objectList, numObjects);
					switch(apRoomContents[object1]->open()){
						case DOOR:
							isComplete = true;
							break;
						case BOX:
							static_cast<DoorKey*>(apRoomContents[DOORKEY])->setVisibility(true);
							break;
						default:
							break;
					}
				}else
					cout << unknownObject;
				break;
			//////////////////////////////////////////////////////////////////
			case CLOSE:
				if(object1 >= 0){
					int DOORKEY = pickFromList("door key", objectList, numObjects);
					switch(apRoomContents[object1]->close()){
						case DOOR:
							isComplete = true;
							break;
						case BOX:
							static_cast<DoorKey*>(apRoomContents[DOORKEY])->setVisibility(false);
							break;
						default:
							break;
					}
				}else
					cout << unknownObject;
				break;
			//////////////////////////////////////////////////////////////////
			default:
					cout << invalidCommand;
				break;
			//////////////////////////////////////////////////////////////////
		}
		cout << std::endl << std::endl;
		printScreenBreak();
	}

	cout << "\nPress any key to continue...";
	cin.get();

	return 0;
}

int pickFromList(const string criteria, const string* list, const int listSize){
	for(int listIndex = 0 ; listIndex < listSize ; listIndex++)
		if(list[listIndex].compare(criteria) == 0)
			return listIndex;					//return index of object on list OR
	return -1;									//return -1 to indicate not on list
}

void listRoomItems(GameObject* thisRoom[], int roomSize){
	for(int i = 0 ; i < roomSize ; i++)
		if(thisRoom[i]->getName().compare("invisible") != 0)
			cout << "\n" << thisRoom[i]->getName();
}

void printScreenBreak()
{
	for (int i = 0 ; i < 80 ; i++)		//80 character places across the screen
		cout << '-';
}