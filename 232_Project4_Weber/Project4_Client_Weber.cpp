#include "table.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int transition(Pair<char, string> Paris);
int action(Pair<char, string> Paris);

int main()
{
	ifstream tableFile;
	char tempArray[5], answer;
	string currentState, nextState;
	int i = 0;
	bool done = false;

	//Table < Pair<int, char>, int> exampleTable(421, function);		
	//Pair<Pair<int, char>, int> p1;
	

	Table < Pair<char, string>, string> tTable(35, transition);
	Table < Pair<char, string>, string> aTable(35, action);
	Pair<Pair<char, string>, string> tempPair;
	Pair<char, string> tempPair2;

	cout << "Do you want to use different tables instead of the included tables? (Y/N)\n";
	cin >> answer;

	if (answer == 'Y')
	{
		cout << "Enter the file path for the transition table.\n";
		cin >> currentState;
		tableFile.open(currentState);
	}
	else tableFile.open("transition_table.txt");

	
	
	for (int i = 0; i < 5; i++)
	{
		tableFile >> tempArray[i];
		//cout << tempArray[i];
	}
	
	//cout << transitionTable.lookUp(tempPair.first);

	//Read transition table
	while (tableFile >> currentState)
	{
		i = 0;
		while (tableFile.peek() != '\n')
		{
			tableFile >> nextState;
			tempPair.first.first = tempArray[i];
			tempPair.first.second = currentState;
			tempPair.second = nextState;
			tTable.insert(tempPair);
			i++;
		}
	}	

	tTable.print();
	
	tableFile.close();

	if (answer == 'Y')
	{
		cout << "Enter the file path for the action table.\n";
		cin >> currentState;
		tableFile.open(currentState);
	}
	else tableFile.open("action_table.txt");

	for (int i = 0; i < 5; i++)
	{
		tableFile >> tempArray[i];
		//cout << tempArray[i];
	}

	// Read action table
	while (tableFile >> currentState)
	{
		if (currentState == "ok3" || currentState == "fa3")
		{
			i = 0;
			while (tableFile.peek() != '\n' && !tableFile.eof())
			{
				
				tableFile >> nextState;
				tempPair.first.first = tempArray[i];
				tempPair.first.second = currentState;
				tempPair.second = nextState;
				aTable.insert(tempPair);
				i++;
			}
		}
	}
	//cout << transitionTable.lookUp(tempPair.first);
	aTable.print();
	
	//Continuously get characters from user and iterate states
	while (!done)
	{		//Get first character
		cout << "Enter the first key and press enter.\n"; 
		cin >> tempPair.first.first;
		tempPair.first.second = "nke";

		while (1)
		{
			//Check for action
			if (tempPair.first.second == "ok3" || tempPair.first.second == "fa3") //There are only actions for these two states	
			{
				if (aTable.lookUp(tempPair.first) == "alarm")		//If state is fa3, sound alarm
				{
					cout << "BEEP BEEP BEEP BEEP BEEP\n";
					cout << "Try again? (Y/N)\n";				    //Ask user if they want to continue
					cin >> answer;
					if (answer == 'N')
						done = true;
					break;
				}

				else if (aTable.lookUp(tempPair.first) == "unlock") //If state is ok3, unlock lock
				{
					cout << "*click*\n";
					cout << "Try again? (Y/N)\n";					//Ask user if they want to continue
					cin >> answer;
					if (answer == 'N')
						done = true;								
					break;
				}

			}
		
			//Get next state
			nextState = tTable.lookUp(tempPair.first);
			tempPair.first.second = nextState;
		
			cout << "Enter the next key and press enter.\n";
			cin >> tempPair.first.first;		//Read in a char
		}
	}
	
	return 0;
}
// Firstly: the demo will consist of running your program with the supplied data. 
// Your program should run as long as the user wants. NOT one 4 character sequence and then exit. 
// It should run multiple times with the same action and transition tables.

// Secondly: your program should  hard code the table file names and load them automatically upon start up. 
// It is fine if your program prints that it is loading the action and transition tables. 
// Certainly have code that makes sure they were loaded successfully.

// Thirdly: The demo will also consist of loading different action and transition tables.( ie a different key sequence to unlock ). 
// These tables will be in exactly the same format as those that were provided.

//So once you have the data loaded in the the appropriate table(actionTableand transitionTable) set up,
//what do you do ?
//initially you are in state nke
//your program eats the first letter(event)
//so now you have a state and event.
//Read action table :
//Any action associated with this pair ? If so, perform it
//Otherwise, read transition table to determine the next state to
//transition to
//Then read next event the user enteredand repeat(obviously a loop through the 4 keys entered)

//int function(Pair<char, string> Paris)
//{
//	if (Paris.second[2] == 'e')		//Case nke
//		return ((Paris.first % 65) * 7);								//In this case there are 7 possible states. Number of possible states given by
//	else if (Paris.second[0] == 'o')	//Case ok						  2(n-1) + 1 where n is the number of keys in the combination
//		return((Paris.first % 65) * 7 + (Paris.second[2] % 48));								//In this case the "ok after" states range from index 1 to 3, with there being 3 spots. 
//	else return ((Paris.first % 65) * 7 + (Paris.second[2] % 45));//case fa						//The index range is 1 to n, with there being n - 1 spots.
//
//	//return ((Paris.first + Paris.second[2]) % 35);
//}


int transition(Pair<char, string> Paris)
{
	if (Paris.second[2] == 'e')		//Case nke
		return ((Paris.first % 65) * 7);								//In this case there are 7 possible states. Number of possible states given by
	else if (Paris.second[0] == 'o')	//Case ok						  2(n-1) + 1 where n is the number of keys in the combination
		return((Paris.first % 65) * 7 + (Paris.second[2] % 48));								//In this case the "ok after" states range from index 1 to 3, with there being 3 spots. 
	else return ((Paris.first % 65) * 7 + (Paris.second[2] % 45));//case fa						//The index range is 1 to n, with there being n - 1 spots.

	//return ((Paris.first + Paris.second[2]) % 35);
}

//Do I need table with array size 35, or do i just need 10? Or 2?
//Do I need a "no action?" What will be the context of the action() call?

int action(Pair<char, string> Paris)
{
	if (Paris.second == "ok3")		//Case ok3
		return (Paris.first % 65);
	else if (Paris.second == "fa3") //Case fa3
		return (Paris.first % 65 + 5);
	else return -1;
}







//Determine tablesize by reading the table
//Declare table after

//Needed space is given by k * (2(n - 1) + 1) 
//Simplified,  k(2n - 1)
//Where k is the number of possible keys and n is the number of keys in the combination


//35 unique keys
//array may not be 35?
//Avoid collisions altogether, or resolve?
//
// 5 letters (ASCII 65-69)
// 7 states
// ok states are same except for 3rd spot (1,2,3)
// fa states are same except for 3rd spot (1,2,3)
// hash(keyValue) = keyValue % tableSize


//Linear collision resolution
// while (the_table[key] already holds a value)
//		key++
// the_table[key] = pair
//
//

