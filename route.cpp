#include "route.h"

// returns distance between two verticies(cities)
int route::getDistance(int x1, int x2, int y1, int y2) {
	double distance_x = x2 - x1;
	double distance_y = y2 - y1;
	double total_distance = sqrt(distance_x*distance_x + distance_y*distance_y);
	return (int) round(total_distance);
};

// adds vertex(city) to 
void route::addCity() {

};
city* route::getCity(int city_id) {
	return cities[city_id];
};
