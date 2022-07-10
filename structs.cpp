/*

Using a Struct to Calculate Bowling Scores
Week 7 Programming Assignment
By Justin Smith
ITCS 2530 V0801

This program will read input from a file, specified as a global constant, and assign that data to an array of
structs. The struct includes one element for the bowler name, an array to hold bowler scores and an element 
to hold the average score for that bowler.

The function PrettyPrintResults is used to show output to user

*/

#include <iostream> // I/O Header File
#include <string> // String header file
#include <fstream> // Header file for file I/O
#include <iomanip> // Header file for format manipulation

using namespace std;

// Global scope constants
const string FILE_NAME = "BowlingScores.txt";
const int NUM_GAMES = 4; // How many games were played
const int NUM_PEOPLE = 10; // Number of people
const char emptyChar = ' '; // Used for end condition in getline function

// Bowler struct is used to hold bowler name, scores, and bowler average
// This program will use an array of this struct to hold data 
struct Bowler
{
	string bowlerName;
	int arrScores[NUM_GAMES];
	int bowlerAverage;
};

Bowler bowlerInfo[NUM_PEOPLE]; // Declare bowlerInfo array of Bowler struct


// For reference, main function begins at line 149


bool GetBowlingData(string FILE_NAME) // Input bowler name and scores into the array of bowlerInfo structs
{
	// Declare file stream variable and open file I/O
	ifstream fs;
	fs.open(FILE_NAME);
	// Check to see if file stream opens correctly
	if (!fs)
	{
		cout << "The file could not be opened. Program exiting" << endl;
		system("pause");
		return false; // Returns value false to main, ends function
	}

	string line;
	
	// Outer for loop inputs the bowler name into the ith element of bowlerInfo.bowlerName
	for (int i = 0; i < NUM_PEOPLE; i++)
	{
		// Each iteration of bowlerInfo array of struct, first input is name
		fs >> bowlerInfo[i].bowlerName;
		getline(fs, line, emptyChar);
		
		for (int j = 0; j < NUM_GAMES; j++)
		{
			// Inner loop inputs the scores into the arrScores array of Bowler struct
			fs >> bowlerInfo[i].arrScores[j]; // Input scores into bowlerInfo.arrscores at index j with data from fs
			// Used if else here to determine which end condition to use in getline function
			// If NUM_GAMES - 1 = j, getline moves past the newline character, which moves to the next line
			// Else the ending condition of getline is specifies as emptyChar (' ') or whitespace and continues on that line
			if (j == NUM_GAMES - 1)
				getline(fs, line);
			else
				getline(fs, line, emptyChar);
		}
	}

	// Close the file stream
	fs.close();

	return true; // Returns bool true to main to indicate that function was successful
}


void GetAverageScores() // Calculate averages and load into bowlerInfo struct
{
	// Need to calculate average, looking at two dimensions
	// One is number of people, one is the number of games
	// Nested for loops are needed to access the correct elements
	// Inner loop adds up scores for each bowler (outer loop) and after calculates the average
	for (int i = 0; i < NUM_PEOPLE; i++)
	{
		bowlerInfo[i].bowlerAverage = 0; 
		// initialed back to zero after inner loop to hold average for next bowler

		for (int j = 0; j < NUM_GAMES; j++)
		{
			// Adds scores to bowlerAverage at index [i][j]
			bowlerInfo[i].bowlerAverage = bowlerInfo[i].bowlerAverage + bowlerInfo[i].arrScores[j]; 
		}
		bowlerInfo[i].bowlerAverage = bowlerInfo[i].bowlerAverage / NUM_GAMES; // Calculation for average 
	}

	return;
}


// Function to print the contents of the file input
// Includes bowler name, scores, and the average for each bowler.
void PrettyPrintResults()
{
	// Header
	cout << setw(80) << left << setfill('#') << "#" << endl;
	cout << setw(24) << left << setfill('#') << "#";
	cout << "  Calculating Bowlers Averages  ";
	cout << setw(24) << right << setfill('#') << "#" << endl;
	cout << setw(80) << left << setfill('#') << "#" << endl << endl;

	// Pretty Print Results
	for (int i = 0; i < NUM_PEOPLE; i++)
	{
		cout << setw(80) << left << setfill('-') << "-" << endl;
		cout << bowlerInfo[i].bowlerName << ": " << endl; // Outputs the bowler name

		for (int j = 0; j < NUM_GAMES; j++)
		{
			cout << "Game " << j + 1 << " - ";
			cout << bowlerInfo[i].arrScores[j] << endl; // Outputs the score for the bowler and game
		}

		cout << "Average score: " << bowlerInfo[i].bowlerAverage << endl; // Outputs average
		cout << setw(80) << left << setfill('-') << "-" << endl << endl;

	}

	system("pause");

	return;
}


// ************************************************************************************** \\
// ****************************************  MAIN  ************************************** \\
// ************************************************************************************** \\


int main()
{
	bool status; // Declare bool variable for return of funtion GetBowlingData

	// Call function GetBowlingData, passing as arguments the file name and the empty array of struct Bowler
	status = GetBowlingData(FILE_NAME);
	// Out the status of function GetBowling if successful or not
	if (status == true)
		cout << "Bowler Scores successfully added..." << endl << endl;
	else
		cout << "Could not read file, please verify your file directory..." << endl << endl;
	
	GetAverageScores(); // Call function GetAverageScores to calculate averages and load into array of structs

	PrettyPrintResults(); // Call function PrettyPrintResults to output results

	return 1;
}