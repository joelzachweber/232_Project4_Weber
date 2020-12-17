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
	
	Table < Pair<char, string>, string> tTable(35, transition);
	Table < Pair<char, string>, string> aTable(35, action);
	Pair<Pair<char, string>, string> tempPair;

	cout << "Do you want to use different tables instead of the included tables? (Y/N)\n";
	cin >> answer;

	// If user wanted to use their own tables, prompt for file path of transition table
	if (answer == 'Y')
	{
		cout << "Enter the file path for the transition table.\n";
		cin >> currentState;
		tableFile.open(currentState);
	}
	// Otherwise, open default transition table
	else tableFile.open("transition_table.txt");

	// Read in letters from table
	for (int i = 0; i < 5; i++)
		tableFile >> tempArray[i];

	// Read transition table
	while (tableFile >> currentState)				//Read in current state
	{
		i = 0;
		while (tableFile.peek() != '\n')			// While on the same line,
		{
			tableFile >> nextState;					// Read in next state 
			tempPair.first.first = tempArray[i];	// Set letter of temporary pair
			tempPair.first.second = currentState;   // Set current state of temporary pair
			tempPair.second = nextState;			// Set next state of temporary pair
			tTable.insert(tempPair);				// Insert temporary pair to table
			i++;
		}
	}	
	
	// Close transition table file
	tableFile.close();

	// If user wanted to use their own tables, prompt for file path of action table
	if (answer == 'Y')
	{
		cout << "Enter the file path for the action table.\n";
		cin >> currentState;
		tableFile.open(currentState);
	}
	else tableFile.open("action_table.txt");

	// Read in letters from table
	for (int i = 0; i < 5; i++)
		tableFile >> tempArray[i];
	
	// Read action table
	while (tableFile >> currentState)								// Read in current state
	{	// There are only actions to read in for the ok3 and fa3 states
		if (currentState == "ok3" || currentState == "fa3")
		{
			i = 0;
			while (tableFile.peek() != '\n' && !tableFile.eof())	// While on same line and not at end of file,
			{
				
				tableFile >> nextState;								// Read in action
				tempPair.first.first = tempArray[i];				// Set letter of temporary pair
				tempPair.first.second = currentState;				// Set current state of temporary pair
				tempPair.second = nextState;						// Set action of temporary pair
				aTable.insert(tempPair);							// Insert temporary pair to table
				i++;
			}
		}
	}
	
	// Continuously let user enter combinations
	while (!done)
	{		
		// Get first character from user and set initial state
		cout << "Enter the first key and press enter.\n"; 
		cin >> tempPair.first.first;		
		tempPair.first.second = "nke";		

		// Continuously get characters from user, iterate state, and perform corresponding action
		while (1)
		{   // Check for action
			if (tempPair.first.second == "ok3" || tempPair.first.second == "fa3") // There are only actions for these two states	
			{
				if (aTable.lookUp(tempPair.first) == "alarm")		// If state is fa3, sound alarm
				{
					cout << "BEEP BEEP BEEP BEEP BEEP\n";
					cout << "Try again? (Y/N)\n";				    // Ask user if they want to continue
					cin >> answer;
					if (answer == 'N')
						done = true;
					break;
				}

				else if (aTable.lookUp(tempPair.first) == "unlock") // If state is ok3, unlock lock
				{
					cout << "*click*\n";
					cout << "Try again? (Y/N)\n";					// Ask user if they want to continue
					cin >> answer;
					if (answer == 'N')
						done = true;								
					break;
				}
			}
		
			// Get next state from transtion table
			nextState = tTable.lookUp(tempPair.first);
			tempPair.first.second = nextState;
		
			// Get next character from user
			cout << "Enter the next key and press enter.\n";
			cin >> tempPair.first.first;		
		}
	}
	
	return 0;
}

int transition(Pair<char, string> Paris)
{
	if (Paris.second[2] == 'e')		//Case nke
		return ((Paris.first % 65) * 7);								//In this case there are 7 possible states. Number of possible states given by
	else if (Paris.second[0] == 'o')	//Case ok						  2(n-1) + 1 where n is the number of keys in the combination
		return((Paris.first % 65) * 7 + (Paris.second[2] % 48));								//In this case the "ok after" states range from index 1 to 3, with there being 3 spots. 
	else return ((Paris.first % 65) * 7 + (Paris.second[2] % 45));//case fa						//The index range is 1 to n, with there being n - 1 spots.

	//return ((Paris.first + Paris.second[2]) % 35);
}

int action(Pair<char, string> Paris)
{
	if (Paris.second == "ok3")		//Case ok3
		return (Paris.first % 65);
	else if (Paris.second == "fa3") //Case fa3
		return (Paris.first % 65 + 5);
	else return -1;
}

