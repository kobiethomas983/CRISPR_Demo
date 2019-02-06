#include <iostream>
#include <vector>

#ifndef _DNASTRAND_
#define _DNASTRAND_
#include "dnasequence.h"
using namespace std;

class DNAStrand {
	public:
		DNAStrand(); 
		// Assume that the strand is made up of 100 sequences.

		DNAStrand(int length);
		// Assume that the strand is made up of length sequences.

		DNAStrand(vector<DNASequence> sequences);
		// Assume that the sequence is initialized to the nucleotides string.

		DNAStrand(const DNAStrand& arg);
		// Copy constructor

		~DNAStrand();
		// Destructor

		DNAStrand& operator=(const DNAStrand& arg);
		// Assignment operator

        friend DNAStrand operator+(const DNAStrand& strand, const DNASequence& seq);
        // Append the given sequence onto the end of the strand.

        friend DNAStrand operator-(const DNAStrand& strand, const DNASequence& seq);
        // Remove the given sequence from the invoking object if it exists. Return
        // the modified sequence. If the given sequence is not found, return the
        // invoking sequence unaltered. Make sure no holes are left in DNAStrand.

		int find(const DNASequence& sequence);
		// find a DNASequence in the DNAStrand

		void replaceSequence(const DNASequence& findSeq, const DNASequence& replaceSeq);
		// find and replace all occurances of sequence.

		int findNth(const DNASequence& sequence, int Nth=1, int startAt = 0);
		// find the Nth occurance DNASequence that matches the given DNASequence.
		// Default to the first occurance and starting at index 0. Using default
		// values, the result should be the same as find above.

		void replaceNthSequence(const DNASequence& findSeq, DNASequence replaceSeq, int Nth = 1, int startAt = 0);
		// find and replace the Nth occurance of sequence starting at startAt.
		// BONUS: +5

		void removeNthSequence(const DNASequence& sequence, int Nth = 1, int startAt = 0);
		// find and remove the Nth occurance of sequence starting at startAt.
		// Default to the first occurance and starting at index 0. Using default
		// values, the result should be the same as operator- above. Make sure no
		// holes are left in DNAStrand array.
		// BONUS: +10

		friend ostream& operator<<(ostream& outs, const DNAStrand& strand);
		// Output operator for the DNAStrand, one sequence per line.

		friend istream& operator>>(istream&  in, DNAStrand& strand);
		// Input operator for the DNAStrand, whitespace separates the
		// DNASequences. Assume that only one DNAStrand will be read in
		// per execution.

		int get_capacity() const { return capacity; };
		int get_num_sequences() const { return num_sequences; };
		const int INCREASE_CAPACITY=25;

	private:
		DNASequence *dna_sequences;				// Dynamic array of DNASequences
		int			 num_sequences;				// Number of sequences.
		int 		 capacity;					// Max sequences.
		void		grow();
};

#endif
