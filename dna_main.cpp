/*:x
 * Test driver for DNAStrand with DNASequences
 * 
 *  -- provides a test for each DNAStrand function and
 *  all but the operator+ function in DNASequence.
 *
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dnasequence.h"
#include "dnastrand.h"

using namespace std;

// ifstream get_dnastrand_file(string& filename)
//
// @param filename: name of the file with DNAStrand data.
// @returns ifstream that points to the open file.
ifstream get_dnastrand_file(string& filename)
{
	ifstream fin;

	// Loop until filename with DNAStrand data is correctly loaded
	// Or the user requested to "quit" the program.
	do {
		cout << "Enter file containing the DNASequences or quit: ";
		cin >> filename;
		if (filename != "quit") {
			fin.open(filename);
			if (fin.fail()) {
				cout << "Invalid filename: " << filename << endl;
			}
		}
	} while (fin.fail() || filename == "quit");

	if (filename == "quit") exit(0);
	return fin;
}

// void reset(istream& in)
//
// @param istream in is a failed input stream that needs to be reset.
// clears the stream and ignores all of the bad input.
void reset(istream& in)
{
	bool failed = true;

	// Fixes the cin stream when user enters bad data.
	do {
		if (failed) {
			failed=false;
			cout << "Invalid input, reseting stream" << endl;
		}

		// Clears out the bad data in cin stream
		in.clear();
		in.ignore();
	} while (in.fail());
}

// int get_menu_option()
//
// @returns the index of the menu option selected by the user
// OR -1 when the user wants to quit. Make sure to keep "Quit"
// as the last option in the vector.
int get_menu_option() {
	int menu_op = -1;
	static vector<string> menu = {
		"New DNAStrand", 
		"Find sequence",
		"Remove sequence",
		"Add Sequence",
		"Replace sequence",
		"Find Nth sequence",
		"Remove Nth sequence",
		"Replace Nth sequence",
		"Splice sequence",
		"Quit"
	};
	
	do {	// Enter the menu option. Make sure input is correct.
		cout << "Enter a CRSPR therapy (0-" << (menu.size()-1) << "): " << endl;

		// Prints out the menu
		for (int i = 0; i < menu.size(); i++) {
			cout << "\t" << i << ") " << menu[i] << endl; 
		}
		// Gets the menu option
		cin >> menu_op;

		// if bad input, it fixes cin.
		if (cin.fail()) reset(cin);
	} while (menu_op < 0 || menu_op > (menu.size()-1));

	// If user wants to quit, it should always be the
	// Last option but we want all quit options to be
	// less than 0.
	if (menu_op == (menu.size()-1)) return -1;
	return menu_op;
}

// int main()
//
// Implements the driver for the DNAStrand testing using DNASequences.
//
int main()
{
	// Implement your test functions here.
	DNAStrand dnastrand;
	DNASequence dnasequence;
	DNASequence replaceSeq, splice;
	string filename;
	int index, menu_op = -1;
	int nth, startAt;
	ifstream fin; 

	do {
		// Read the DNAStrand file made up of DNASequences
		fin = get_dnastrand_file(filename);
		fin >> dnastrand;
		if (! fin.eof() && fin.fail()) {
			cout << "Error: failed to read file: " << filename << endl;
		}
		cout << "New DNAStrand:\n" << dnastrand << endl;

		// Perform the operators using the current DNAStrand, can replace
		// the DNAStrand with option 0.
		do {
			menu_op = get_menu_option();

			// All operations except New DNAStrand and Quit use a DNASequence
			if (menu_op > 0) {
				cout << "Enter DNASequence for CRSPR operation: ";
				cin >> dnasequence;
			}

			// Choose operation from the menu_op
			switch(menu_op) {
				case 0:		// New DNAStrand - loops to outer loop to read a new DNAStrand file
					break;

				case 1:		// Find - find the DNASequence in the DNAStrand and return the index.
				index = dnastrand.find(dnasequence);	
					if (index != -1)
						cout << "Found " << dnasequence << " at " << index << endl;
					else
						cout << "Not Found " << dnasequence << endl;
					break;

				case 2:		// Remove - remove the DNASequence from the DNAStrand
					dnastrand = dnastrand - dnasequence;
					break;

				case 3:		// Add - add the DNASequence to the end of the DNAStrand
					dnastrand = dnastrand + dnasequence;
					break;

				case 4:		// Replace - replace the given DNASequence with the new given DNASequence
					cout << "Enter new sequence for replacing: ";
					cin >> replaceSeq;
					dnastrand.replaceSequence(dnasequence, replaceSeq);
					break;

				case 5:		// Find Nth - find the nth occurrance of the DNASequence starting at startAt.
					cout << "Enter a starting point: (0-" << dnastrand.get_num_sequences() << "): ";
					cin >> startAt;
					cout << "Enter an Nth occurrance: ";
					cin >> nth;
					index = dnastrand.findNth(dnasequence, nth, startAt);
					if (index != -1)
						cout << "Found " << dnasequence << " at " << index << endl;
					else
						cout << "Not Found " << dnasequence << endl;
					break;

				case 6:		// Remove Nth - find and remove the nth occurrance of the DNASequence starting at startAt
					cout << "Enter a starting point: (0-" << dnastrand.get_num_sequences() << "): ";
					cin >> startAt;
					cout << "Enter an Nth occurrance: ";
					cin >> nth;
					dnastrand.removeNthSequence(dnasequence, nth, startAt);
					break;

				case 7:		// Replace Nth - replace the nth occurrance of the DNASequence starting at startAt
					cout << "Enter a starting point: (0-" << dnastrand.get_num_sequences() << "): ";
					cin >> startAt;
					cout << "Enter an Nth occurrance: ";
					cin >> nth;
					cout << "Enter new sequence for replacing: ";
					cin >> replaceSeq;
					dnastrand.replaceNthSequence(dnasequence, replaceSeq, nth, startAt);
					break;

				case 8:		// Splice - finds and removes a slice of the DNASequence and replaces it throughout the DNAStrand
					cout << "Enter a splice to subtract: ";
					cin >> splice;
					replaceSeq = dnasequence - splice;
					cout << "Replace " << dnasequence << " with " << replaceSeq << endl;

					// Loops over the DNAStrand replacing all occurrances of DNASequence with the spliced sequence.
					do {
						index = dnastrand.findNth(dnasequence, 1, index);
						if (index != -1) {
							dnastrand.replaceNthSequence(dnasequence, replaceSeq, 1, index);
							index++;
						}
						cout << "loop " ;
					} while (index != -1);
					break;

				case -1:	// Quit
					cout << "BYE" << endl;
					filename="quit";
					break;

				default:
					cout << "Error: Should never get here!" << endl;

			}
			// Print DNAStrand only when last operation was on the current DNAStrand
			if (menu_op > 0) 
				cout << dnastrand << endl;
		} while (menu_op > 0);				// Loop as long as not Quit or New DNAStrand

	} while (fin.fail() && filename != "quit");
	return 0;
}
