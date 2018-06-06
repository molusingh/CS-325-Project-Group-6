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
#include <limits>

using std::cin; 
using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::ifstream;
using std::ofstream;
using std::round;

using namespace std;

/*
 * city struct definition
 */
struct city 
{
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
vector<city*> nearestNeighbor(vector<city*>);

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
vector<city*> getInput(string fileName) 
{
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
void outputResults(string fileName, vector<city*> route) 
{
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
int distance(city* a, city* b) 
{
	if (a == NULL || b == NULL) // error case
	{
		cout << "Tring to calculate distance of NULL city" << endl;
		exit(4);
	}
	int xDiff = b->x - a->x;
	int yDiff = b->y - a->y;
	return round(sqrt((xDiff * xDiff) + (yDiff * yDiff))); 
}  


/*
 * Returns the length of the inputed route
 */
int length(vector<city*> route)
{ 
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
vector<city*> optSwap(int i, int j, vector<city*>* route)
{
	if (i > route->size() || j > route->size()) // error case
	{
		cout << "invalid route!" << endl;
		exit(5);
	}
	
	vector<city*> newTour;

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
vector<city*> twoOpt(vector<city*> route)
{
	int improvements = 0;
	int shortest = length(route);
	vector<city*> bestRoute = route;

	int iters = 0;
	while(shortest > (1.25 * 108159)){
		iters++;
		for(int i = 0; i < route.size() -1; i++){
			for(int j = i; j < route.size(); j++){
				vector<city*> newRoute = optSwap(i, j, &bestRoute);
				if(length(newRoute) <  shortest){
					shortest = length(newRoute);
					improvements = 0;
					bestRoute = newRoute;
				}
				else {
					improvements++;
				}
			}
		}
	}
	cout << "iters:" << iters << endl;
	return bestRoute;
}

/*
 * Main program, runs programmed described above
 */
int main(int argc, char** argv) 
{
	string inputFile, outputFile;

	if (argc >= 2) // if argument with filename passed
	{
		inputFile = argv[1];
	}

	else // if no command line arguments
	{
		// get filename	
		cout << "Please input file name: " << endl; 
		cin >> inputFile; 
	}

	outputFile = inputFile + ".tour";

	// get input from file specified, save in route
	vector<city*> route = getInput(inputFile);

	//vector<city*> greedyRoute	= nearestNeighbor(route);

	// implement algorithm
	//!!!! don't forget to pass greedyRoute if nearestNeighbor has been run!!!!!
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


vector<city*> nearestNeighbor(vector<city*> route){
	//the vector to return and a vector of the same size as route
	//in order to track which cities have been pushed to greedyRoute
	vector<city*> greedyRoute;
	vector<int> visited;
	for(int idx = 0; idx < route.size(); idx++){
		visited.push_back(0);
	}

	//grab the first city and mark it as visited
	greedyRoute.push_back(route.at(0));
	visited.at(0) = 1;

	//loop route.size()-1 times (thats how many cities still need to be grabbed)
	//each iteration, find min distance between a city still in route and the last
	//city pushed to greedyroute
	int minDist, minIdx;

	for(int i = 1; i < route.size(); i++){
		minDist = numeric_limits<double>::infinity();
		minIdx	= -1;
		for(int j = 1; j < route.size(); i++){
			if(visited.at(j) == 0 && distance(greedyRoute.at(i-1), route.at(j)) < minDist){
				minDist = distance(greedyRoute.at(i-1), route.at(j));
				minIdx = j;
			}
		}
		visited.at(minIdx) = 1;
		greedyRoute.push_back(route.at(minIdx));
	}

	//debug makes sure loop runs appropriate number of times
	if(route.size() != greedyRoute.size()){
		cout << "nearestNeighbor	not catching all cities in original tour" << endl;
		exit(2);
	}

	return greedyRoute;
}