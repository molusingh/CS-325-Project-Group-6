#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath> 

using std::cin; 
using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::ifstream;
using std::ofstream;

struct city {
	int id;
	int x;
	int y;
};

vector<city*> getInput(string fileName);
void outputResults(string fileName, vector<city*> route); 

vector<city*> getInput(string fileName) {

	// open the input file
	ifstream inputFile;
	inputFile.open(fileName);

	// create empty route to store information 
	vector<city*> route; 
	
	// save each line into a city struct
	int id, x, y;
	while (inputFile >> id >> x >> y) {
		struct city* newCity = new struct city;
		(*newCity).id = id;
		(*newCity).x = x;
		(*newCity).y = y;
		route.push_back(newCity);
	}
	inputFile.close();
	
	// return route
	return route;
}

void outputResults(string fileName, vector<city*> route) {

	// open the output file
	ofstream outputFile;
	outputFile.open(fileName);

	// print size of the route
	outputFile << route.size() << endl;

	// print the qualities of each city in route (in order)
	for (int i = 0; i < route.size(); i++) {
		outputFile << (*route[i]).id << " " << (*route[i]).x << " " << (*route[i]).y << endl;
	}
	
	// close file
	outputFile.close();

}


int main() {

	// get filename
	cout << "Please input file name: " << endl; 
	string inputFile, outputFile;
	cin >> inputFile; 
	outputFile = inputFile + ".tour";

	// get input from file specified, save in route
	vector<city*> route = getInput(inputFile);
	
	// implement algorithm

	// output results to file
	outputResults(outputFile, route); 

	return 0;
}

// Reference:
// L. Zhang. CS 162. Class Lecture, Topic: "File I/O part 1." College of Engineering, Oregon State University, Corvallis, OR., Feb. 2017.
