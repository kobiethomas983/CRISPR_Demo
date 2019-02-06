#include <iostream>
#include <string>

#ifndef _DNASEQUENCE_
#define _DNASEQUENCE_
using namespace std;

// class DNASequence 
//
// A class that contains a sequence of nucleotides in the dna_sequence.
// The max_sequence represents the capacity of the dna_sequence.
// A dna_sequence is a c-string of characters that consist only of
// 'A', 'T', 'G', 'C' standing for the 4 nucleotides and ending in a '\0'
// character. Input into the DNASequence is case-insensitive meaning that
// lower or upper case is acceptable, but it should be converted to uppercase
// internally.
//
class DNASequence {
	public:
		DNASequence(); 
		// Assume that the strand is made up of 100 sequences.

		DNASequence(int length);
		// Assume that the strand is made up of length sequences.

		DNASequence(string nucleotides);
		// Assume that the sequence is initialized to the nucleotides string.

		DNASequence(const DNASequence& arg);
		// Copy constructor

		~DNASequence();
		// Destructor

		DNASequence& operator=(const DNASequence& arg);
		// Assignment operator

		bool operator==(const DNASequence& arg);
		// Equals operator compares the given sequence with the invoking object.

		friend DNASequence operator+(const DNASequence& arg1, const DNASequence& arg2);
		// Append the given sequence onto the end of a copy of the invoking object sequence.

		friend DNASequence operator-(const DNASequence& arg1, const DNASequence& arg2);
		// Remove the given sequence from a copy of the invoking object if it exists. Return
		// the modified sequence. If the given sequence is not found, return the
		// invoking sequence unaltered.

		friend istream& operator>>(istream& ins, DNASequence& arg);
		// Implement the friend function to read in a nucleotide sequence made up
		// of only the following characters: adenine (A), thymine (T), guanine (G)
		// and cytosine (C). Assume case insensitive but convert to upper internally.
		
		friend ostream& operator<<(ostream& out, const DNASequence& arg);
		// Implement the friend function to write out a nucleotide sequence. No blanks.

		int get_max_sequence() const { return max_sequence; };
		// Accessor for max_sequence.

		char* get_dna_sequence() const { return dna_sequence; };
		// Accessor for dna_sequence.

		
	private:
		char		*dna_sequence;				// Dynamic array of char
		int 		max_sequence;				// Number of sequences.
};

#endif
