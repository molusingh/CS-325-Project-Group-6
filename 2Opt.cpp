#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include <cmath>
#include<algorithm>

using namespace std;

struct city{
	int id;
	int x;
	int y;
};

int distance(city*, city*);
int length(vector<city*> route);

int main(int argc, char** argv){

	/*_________________________________Input and allocate memory associated with route_______________________________*/
	string inputFile = argv[1];
	ifstream input;
	input.open(inputFile);

	vector<city*> route;

	int id, x, y;
	while(input >> id >> x >> y){
		city* newCity = new city;
		newCity->id = id;
		newCity->x = x;
		newCity->y = y;

		route.push_back(newCity);
	}

	/*______________________________________Create distance array ____________________________________________________*/

	vector<vector<int>*> distMatrix;
	for(int i = 0; i < route.size(); i++){
		vector<int>* distCol = new vector<int>;
		distMatrix.push_back(distCol);
		for(int j = 0; j < route.size(); j++){
			distMatrix.at(i)->push_back(distance(route.at(i), route.at(j)));
		}
	}

	/*_______________________________________Carry out 2Opt___________________________________________________________*/

	int routeLength = length(route);
	int thisLength = -1;
	int minI = -1;
	int minJ = -1;
	int minLength = routeLength;
	for(int i = 0; i < route.size() -1; i++){
		for(int j = i; j < route.size(); j++){

			if(i==0 && j == route.size()){
				thisLength = routeLength;
			}
			else if( i == 0){
				thisLength = routeLength;
				thisLength -= (distMatrix.at(i)->at(route.size()) - distMatrix.at(j)->at(j+1));
				thisLength += (distMatrix.at(j)->at(route.size()) + distMatrix.at(i)->at(route.size()));
			}
			else if(j == route.size()){
				thisLength = routeLength;
				thisLength -= distMatrix.at(j)->at(0) - distMatrix.at(i)->at(i-1);
				thisLength += distMatrix.at(i)->at(0) + distMatrix.at(j)->at(i-1);
			}
			else{
				thisLength = routeLength;
				thisLength -= distMatrix.at(i)->at(i-1) - distMatrix.at(j)->at(j+1);
				thisLength += distMatrix.at(i)->at(j+1) + distMatrix.at(j)->at(i-1);
			}

			if(thisLength < minLength){
				minI = i;
				minJ = j;
				minLength = thisLength;
			}
		}
	}

	/*__________________________Perform the appropriate swap on the cities____________________________________________*/
	
	vector<city*> newRoute;
	if(minI != -1 && minJ != -1){

		// append new route/tour with cities up to index i  
		for(int idx = 0; idx < minI; idx++){
			newRoute.push_back(route.at(idx));
		}

		// append new route/tour with cities from indexes j to i (backwards)  
		for(int idx = minI; idx <= minJ; idx++){
			newRoute.push_back(route.at(minJ - (idx - minI)));
		}

		// append new route/tour with cities from indices j+1 to end of route
		for(int idx = minJ+1; idx < route.size(); idx++){
			newRoute.push_back(route.at(idx));
		}

		/*______________________________________Destroy distance array ____________________________________________________*/

		for(int i = 0; i < route.size(); i++){
			delete distMatrix.at(i);
		}
	}

	/*_____________________________________Output and free memory associated with route_______________________________*/
	string outputFile = inputFile + ".tour";
	ofstream output;
	output.open(outputFile);

	output << minLength << endl;
	for(int i = 0; i < route.size(); i++){
		output << newRoute.at(i)->id  << " " << newRoute.at(i)->x  << " " << newRoute.at(i)->y << endl;
	}

	return 0;
}

int distance(city* a, city* b) 
{
	// error case: when cities are null
	if (a == NULL || b == NULL) 
	{
		cout << "Tring to calculate distance of NULL city" << endl;
		exit(4);
	}

	// get difference in x and y coordinates 
	int xDiff = b->x - a->x;
	int yDiff = b->y - a->y;

	// pythagorean theorem (rounded) to find distance 	
	return round(sqrt((xDiff * xDiff) + (yDiff * yDiff))); 
} 

int length(vector<city*> route)
{ 
	int m = 0; 

	// iterate through route 
	// sum up the distance between city and previous city
	for (int idx = 1; idx < route.size(); idx++) {
		m += distance(route.at(idx - 1), route.at(idx)); 
	} 

	// add the distance between final and first city 
	m += distance(route.at(route.size()-1), route.at(0));

	return m; 
}