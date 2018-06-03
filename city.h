#ifndef city_h
#define city_h

#include "math.h"
#include <vector>

using namespace std; 

class city {
public:
	city();
	~city();
	bool isCandidate();
	int getID();
	int getX();
	int getY();
	int distance(city*);

private:
	int id;
	int x;
	int y;
	bool visited;
};

#endif