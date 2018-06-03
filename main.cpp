#include "city.h"
#include "route.h"

#include <iostream>
#include <fstream>

int main() {

	// open the input file
	ifstream input_file("data.input");

	// check for successful opening
	if (!input_file.is_open()) {
		cout << "Error: File could not be opened." << endl;
	}

	// read file
	

	// close file
	input_file.close();

	return 0;
}