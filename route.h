#ifndef route_h
#define route_h

#include "city.h"

class route {
public:
	int getDistance(int, int, int, int);
	void addCity();
	city* getCity(int);
private:
	vector<city*> cities;

};

#endif

