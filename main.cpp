#include "city.h"
#include "route.h"

#include <iostream>
#include <fstream>

int main() {

	// open the input file
	ifstream input_file("data.input"); 

	// check for successful opening
	if (!input_file.is_open()) {
		cout << "Error: Input File could not be opened." << endl;
		return 1;
	}

	// read as 

	// read file
	// create vector of cities
	while (!input_file.eof()) {
	// read three ints

	// make into city object

	// add to vector

	}
	// close file
	input_file.close();
	

	// create graph map[start][end]
	// calc distance (weight) between two cities
	// call 2-opt
	//output 

	// open the output file
	ofstream output_file("data.output");
	
	// check for successful opening
	if (!output_file.is_open()) { 
		cout << "Error: Output file could not be opened." << endl;
		return 1;
	}
	// close file
	output_file.close();

	return 0;
}
