/*
 * CS 325 Project Group 6
 * Members: Jacob Garcia, Anmolbir Mann, Natasha Kvalve, Matthew Krilanovich
 * Description: implementation of otp-2 on TSP problem
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cmath> 

using std::cin; 
using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::ifstream;
using std::ofstream;

using namespace std;

/*
 * city struct definition
 */
struct city {
	int id;
	int x;
	int y;
};
typedef struct city city;

// function prototypes
string cityToString(city*);
vector<city*> getInput(string);
void outputResults(string, vector<city*>); 
int distance(city*, city*); 
int length(vector<city*>);
vector<city*> optSwap(int, int, vector<city*>*);
vector<city*> twoOpt(vector<city*>);

/*
 * Returns the string value of an inputed city
 */
string cityToString(city* input)
{
	string toReturn = "NULL";
	string space(" ");
	if (input != NULL)
	{
		toReturn = to_string(input->id) + space + to_string(input->x) + space;
		toReturn += to_string(input->y); 
	}
	return toReturn;
}

/*
 * Returns a route from the inputed file
 */
vector<city*> getInput(string fileName) {

	// open the input file
	ifstream inputFile;

	inputFile.open(fileName);

	// if failed to open file
	if(!inputFile.is_open())
	{
		cout << "Failed to open file " << fileName << endl;
		exit(3);
		
	}
	// create empty route to store information 
	vector<city*> route; 
	
	// save each line into a city struct
	int id, x, y;
	while (inputFile >> id >> x >> y) {
		city* newCity = new city;
		newCity->id = id;
		newCity->x = x;
		newCity->y = y;
		route.push_back(newCity);
	}
	inputFile.close();
	
	// return route
	return route;
}

/*
 * Outputs the inputed route to a the given file
 */
void outputResults(string fileName, vector<city*> route) {

	// open the output file
	ofstream outputFile;
	outputFile.open(fileName);

	// print length of the route
	outputFile << length(route) << endl;

	// print the qualities of each city in route (in order)
	for (int i = 0; i < route.size(); i++) {
		outputFile << cityToString(route.at(i)) << endl;
	}
	
	// close file
	outputFile.close();

}

/*
 * Returns the distance between two cities
 */
int distance(city* a, city* b) {
	if (a == NULL || b == NULL)
	{
		// cout << "Tring to calculate distanc of NULL city" << endl;
		//exit(4);
		return 0;
	}
	int xDiff = b->x - a->x;
	int yDiff = b->y - a->y;
	return sqrt((xDiff * xDiff) + (yDiff * yDiff)); 
}  


/*
 * Returns the length of the inputed route
 */
int length(vector<city*> route) { 
	int m = 0; 
	for (int idx = 1; idx < route.size(); idx++) {
		m += distance(route.at(idx - 1), route.at(idx)); 
	} 

	m += distance(route.at(route.size()-1), route.at(0));

	return m; 
}

/*
 * opt swap helper function
 */
vector<city*> optSwap(int i, int j, vector<city*>* route){
	vector<city*> newTour;
	cout << i << "," << j << "\t";
	for (int s = 0; s < route->size(); ++s)
	{
		cout << cityToString(route->at(s)) << "\t";
	}
	cout << endl;

	for(int idx = 0; idx < i; idx++){
		newTour.push_back(route->at(idx));
	}
	for(int idx = i; idx <= j; idx++){
		newTour.push_back(route->at(j - (idx - i)));
	}
	for(int idx = j+1; idx < route->size(); idx++){
		newTour.push_back(route->at(idx));
	}
	return newTour;
}

/*
 * 2 opt algorithm
 */
vector<city*> twoOpt(vector<city*> route){

	int improvements = 0;
	int shortest = length(route);
	vector<city*>* bestRoute = &route;

	while(improvements < 500){
		for(int i = 0; i < route.size() -1; i++){
			for(int j = i; j < route.size(); j++){
				vector<city*> newRoute = optSwap(i, j, bestRoute);
				if(length(newRoute) <  shortest){
					shortest = length(newRoute);
					improvements = 0;
					bestRoute = &newRoute;
					cout << "Switch" << endl;
				}
				else {
					improvements++;
				}
			}
		}
	}
	return *bestRoute;
}

/*
 * Main program, runs programmed described above
 */
int main() {

	// get filename
	cout << "Please input file name: " << endl; 
	string inputFile, outputFile;
	cin >> inputFile; 
	outputFile = inputFile + ".tour";

	// get input from file specified, save in route
	vector<city*> route = getInput(inputFile);

	// implement algorithm
	vector<city*> bestRoute = twoOpt(route);


	// output results to file
	outputResults(outputFile, bestRoute); 

	int routeSize = route.size();
	for (int i = 0; i < routeSize; ++i)
	{
		delete route.at(i);
	}

	return 0;
}

// Reference:
// L. Zhang. CS 162. Class Lecture, Topic: "File I/O part 1." 
// College of Engineering, Oregon State University, Corvallis, OR., Feb. 2017.
