#include <iostream>
#include <vector>
#include "dnasequence.h"
#include "dnastrand.h"

using namespace std;

// Assume that the DNAStrand can contain up to 100 sequences.
DNAStrand::DNAStrand() : capacity(100)
{
	num_sequences = 0;
	dna_sequences = new DNASequence[capacity];

}
 

// Assume that the DNAStrand can contain up of length sequences.
DNAStrand::DNAStrand(int size) : capacity(size)
{
	dna_sequences = new DNASequence[size];
	num_sequences = 0;

}

// Assume that the DNAStrand is initialized to the DNASequences in the vector.
// store the sequences into dna_sequences
//
DNAStrand::DNAStrand(vector<DNASequence> sequences) : capacity(sequences.capacity())
{
	//if the capacity is at zero add on the INCREASE_CAPACITY
	if(capacity == 0)
	{
		capacity = capacity+INCREASE_CAPACITY;
	}
	
	dna_sequences = new DNASequence[capacity];
	for(int i = 0; i < sequences.size();i++)
	{
		dna_sequences[i] = sequences[i];
	}
		num_sequences = sequences.size(); 	
	
}

// Implement the Copy constructor(like a duplicate of each object)
//copy arg sequence to the dna sequence 
//copy num seq to arg num sequence
DNAStrand::DNAStrand(const DNAStrand& arg) : capacity(arg.capacity)
{
	dna_sequences = new DNASequence[capacity]; 
	
	for(int i = 0; i < arg.num_sequences;i++)
	{
		dna_sequences[i] = arg.dna_sequences[i];
	}		
	num_sequences = arg.num_sequences;
}

// Implement Destructor
DNAStrand::~DNAStrand()
{
	
	 delete [] dna_sequences;

}

// Implement the Assignment operator
// if the sequence is larger than the cap resize the array 
// store arg.dna_seq into dna_seq
DNAStrand& DNAStrand::operator=(const DNAStrand& arg)
{
	if(this != &arg)
	{
		if(capacity < arg.num_sequences)
		{
			delete [] dna_sequences;
			capacity = arg.capacity;
			dna_sequences = new DNASequence[capacity];
		}
		for(num_sequences = 0; num_sequences < arg.num_sequences; num_sequences++)	
		{
			dna_sequences[num_sequences] = arg.dna_sequences[num_sequences];
		}
	}
		
	
	return *this;
}

// Implement operator+ to append the given sequence onto the end of the DNAStrand.
//if the capacity is less than the number of sequences grow the result
DNAStrand operator+(const DNAStrand& strand, const DNASequence& seq)
{
 	DNAStrand result = strand;
        if(result.capacity < result.num_sequences+1)
        {
                result.grow();
        }
        result.dna_sequences[result.num_sequences++] = seq;
        return result;
}

// Implement operator- to remove the given DNASequence from a copy of DNAStrand. 
// Return the modified sequence. If the given sequence is not found, return the
// invoking sequence unaltered. Make sure no holes are left in DNAStrand.
DNAStrand operator-(const DNAStrand& strand, const DNASequence& seq)
{
	DNAStrand result = strand;

	for(int i = 0; i < result.num_sequences; i++) 
	{
		if(result.dna_sequences[i] == seq)
		{
			for(int j = i; j < result.num_sequences-1;j++)
			{
				result.dna_sequences[j] = result.dna_sequences[j+1];
			}

			result.num_sequences = result.num_sequences - 1;
			return result;
		}			

	}
	return result;
}

// Implement find to locate a DNASequence in the DNAStrand
// return the index if found or -1 if not found.
int DNAStrand::find(const DNASequence& sequence) 
{
	//for loop loops through the dna_sequence
	for(int i = 0; i < num_sequences;i++)
	{
		if(dna_sequences[i] == sequence)
			return i;
	} 

	return -1;
}

// Implement find and replace all occurances of DNASequence in the DNAStrand.
void DNAStrand::replaceSequence(const DNASequence& findSeq, const DNASequence& replaceSeq)
{
	if(int i = find(findSeq) != -1)
	{
		dna_sequences[i] = replaceSeq;
	}	
	

}
// Implement find the Nth occurance DNASequence that matches the given DNASequence.
// Default to the first occurance and starting at index 0. Using default
// values, the result should be the same as find above.
// BONUS: +5
int DNAStrand::findNth(const DNASequence& sequence, int Nth, int startAt)
{
	
	cout << "findNth::Not implemented yet" << endl;
	return -1;
}

// Implement find and replace the Nth occurance of DNASequence starting at startAt.
// BONUS: +5
void DNAStrand::replaceNthSequence(const DNASequence& findSeq, DNASequence replaceSeq,
								 int Nth, int startAt)
{
	cout << "replaceNthSequence::Not implemented yet" << endl;
}

// Implement find and remove the Nth occurance of the given DNASequence starting
// at startAt. Default to the first occurance and startAt index 0. Using default
// values, the result should be the same as operator- above. Make sure no holes
// are left in DNAStrand array.
// BONUS: +10
void DNAStrand::removeNthSequence(const DNASequence& sequence, int Nth, int startAt)
{
	cout << "removeNthSequence::Not implemented yet" << endl;
}

// Implement the insertion (Output) operator to output the DNAStrand
// Output one DNASequence per line.
ostream& operator<<(ostream& outs, const DNAStrand& strand)
{
	for(int i = 0; i < strand.num_sequences;i++)
	{
		outs << strand.dna_sequences[i] << endl; 

	}
	return outs;
}

// Implement the Extraction (input) operator to input the DNAStrand
// Input should be case insensitive but convert to upper. Make sure
// that only valid nucleotides are included in the DNAStrand. Use the
// fact that each string is a DNASequence. [HINT: consider using the
// constructor that takes a vector<DNASequence> to initialize DNAStrand.]
istream& operator>>(istream&  in, DNAStrand& strand)
{
	//new variable of type DNASequence 
	DNASequence Dseq;
	
	//create a vector of the sequences 
	vector<DNASequence> Seq;
	while(in >> Dseq)
	{
		Seq.push_back(Dseq);
			
	}
	
	//assign the strand of sequences to strand
	strand = DNAStrand(Seq);

	return in;
}

// Implement the function to grow the array of DNASequences and copy elements
// from the old smaller array to the new bigger array. Update the capacity.
// Use the private grow function anywhere the internal array has to grow.
void DNAStrand::grow() 
{
	//This allows you to create a larger array
	capacity += INCREASE_CAPACITY;
	//create a new dynamic array of type DNASequence 
	DNASequence *added_sequences = new DNASequence[capacity];
	
	//put elements from the old array into the new array
	for(int i = 0; i < num_sequences; i++)
	{
		added_sequences[i] = dna_sequences[i];
	}
	
	//delete old array 
	delete [] dna_sequences;

	cout << "grow::Not implemented yet" << endl;
}

