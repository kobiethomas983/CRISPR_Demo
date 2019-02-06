#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include "dnasequence.h"

using namespace std;
bool validate (string);

// Assume that the strand is made up of 100 sequences.
DNASequence::DNASequence() : max_sequence(100) 
{
	dna_sequence = new char[max_sequence + 1]; 
	dna_sequence[0] = '\0';
}

// Assume that the strand is made up of length sequences.
DNASequence::DNASequence(int length) : max_sequence(length)
{
	dna_sequence = new char[max_sequence + 1];
	dna_sequence[0] = '\0';
}

// Assume that the sequence is initialized to the nucleotides string.
DNASequence::DNASequence(string nucleotides)
{
	//if their input is valid 
	//assign the capacity to the length
	//set all input to uppercase letters
	//if input not valid call constructor
	if(validate(nucleotides))
	{	max_sequence = nucleotides.length(); 
		dna_sequence = new char[max_sequence+1];
		
		for(int i = 0; i < max_sequence;i++)
		{
			nucleotides[i] = toupper (nucleotides[i]);
		}
		strcpy(dna_sequence,nucleotides.c_str());
	}
	else
	{
		DNASequence();
	}
}

// Copy constructor
DNASequence::DNASequence(const DNASequence& arg) : max_sequence(arg.max_sequence)
{
	dna_sequence = new char[max_sequence+1];
	strcpy(dna_sequence,arg.dna_sequence);
}

// Destructor
DNASequence::~DNASequence()
{
	delete [] dna_sequence;
}

// Assignment operator
DNASequence& DNASequence::operator=(const DNASequence& arg)
{
		//if left hand side doesn't equal right hand side
		//check if the capacity is smaller the arg length
		//if so resize
		if(this != &arg)
		{
			if(max_sequence < strlen(arg.dna_sequence))
			{
				
				delete [] dna_sequence;
				max_sequence = arg.max_sequence;
				dna_sequence = new char[max_sequence+1];
			}
		}
	
    			strcpy(dna_sequence,arg.dna_sequence);
	
			
    	return *this;
		
	
}

// Equals operator compares the given sequence with the invoking object.
bool DNASequence::operator==(const DNASequence& arg)
{
	//compare the two sequences 
	//if equals zero then they are equal
	return(strcmp(dna_sequence,arg.dna_sequence) == 0);
	
}


// Append the given sequence onto the end of the invoking object sequence.
// assign result and check if the capacity is big enough to take in ar1 amd arg2
// if the two length together are larger than the capacity then create room
DNASequence operator+(const DNASequence& arg1, const DNASequence& arg2)
{
    DNASequence result;
	result.max_sequence = arg1.max_sequence;
	if(result.max_sequence < strlen(arg1.dna_sequence)+strlen(arg2.dna_sequence))
    	{
		//see if deletes required 
		int full_len = strlen(arg1.dna_sequence)+strlen(arg2.dna_sequence); 
		if( result.max_sequence < full_len)
		{
			result.max_sequence = full_len; 
			delete [] result.dna_sequence;
		
			result.dna_sequence = new char[result.max_sequence];
		}
	}		
			strcpy(result.dna_sequence, arg1.dna_sequence);
			strcat(result.dna_sequence, arg2.dna_sequence);
	
	
	
    	return result;

}

// Remove the given sequence from the invoking object if it exists. Return
// the modified sequence. If the given sequence is not found, return the
// first argument sequence unaltered.
// use find function to look for arg2 sequence 
//subtract it from arg1 and assign the result to result
DNASequence operator-(const DNASequence& arg1, const DNASequence& arg2)
{
	DNASequence result = arg1;
	string strarg1 = arg1.dna_sequence;
	string strarg2 = arg2.dna_sequence;
	

	size_t found = strarg1.find(strarg2);
	if(found!=string::npos)
	{
		delete [] result.dna_sequence;
		result.max_sequence = arg1.max_sequence - arg2.max_sequence;
		result.dna_sequence = new char [result.max_sequence]; 
		size_t i = found;
	
		for(int i =0; i < result.max_sequence; i++)
		{	
			result.dna_sequence[i] = strarg1[i];

		}
  		
		for(size_t j = found + strarg2.length(); j < strarg1.length();j++)
		{
			result.dna_sequence[i] = strarg1[j];
			i++;
		} 
	} 
cout << "operator-::Not implemented yet" << endl;
	return result;

}

// To make the code compile, a function that validates the input string
// is made up purely of nucleotides.
bool validate(string str) 
{
	// Check the string for characters 'A', 'a', 'T', 't', 'G', 'g', 'C', 'c'
	// return false if any characters in the string are different. You can
	// use any means you like, remember what we did with palindrome code to
	// avoid a big if statement.
	
	bool valid = true;
	 	

	//Create a string with all of the nucleotide characters
	
	for(int i = 0; i < str.length();i++)
	{
		char c = str[i];
		
		if( c == 'a' || c == 'A')
			return valid;
		else if(c == 'T' || c == 't')
			return valid;
		else if(c == 'G' || c == 'g')
			return valid;
		else if(c == 'C' || c == 'c')
			return valid;
		else 
			valid = false;	
	}

return valid;
}

// Implement the friend function to read in a nucleotide sequence made up
// of only the following characters: adenine (A), thymine (T), guanine (G)
// and cytosine (C). Assume case insensitive but convert to upper internally.

istream& operator>>(istream& ins, DNASequence& arg)
{
	string str;
	//reads from t`he input stream 	
	if(ins >> str)
	{
		//is this a valid DNASequence (contains only nucleotides)
		if(validate(str))
		{
			//use the constructor that takes a string and the 
			//assingment operator to deal with the object. It
			//is not the most efficient but it is the cleanest!
				arg = DNASequence(str);
				
			
		
		}
		else
		{
			//what to do with invalid characters found.
			//the DNAsequence arg is unchanged.

			ins.setstate(ios::failbit);
		
		}
	}
	 else 
	{
		// What to do when we hit a different kind of error on input
		// Most likely will be EOF. DNASequence arg is unchanged.
		ins.setstate(ios::failbit);
	}
    return ins;

	    cout << "operator>>::Not implemented yet" << endl;

}

// Implement the friend function to write out a nucleotide sequence. No blanks.
ostream& operator<<(ostream& out, const DNASequence& arg)
{
 	//show the sequence 
	out << arg.dna_sequence;   
    return out;
}


