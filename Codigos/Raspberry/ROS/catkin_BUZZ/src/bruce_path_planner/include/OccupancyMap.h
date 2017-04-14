#ifndef OCCUPANCYMAPBUZZ_H
#define OCCUPANCYMAPBUZZ_H

#include <vector>
#include "nav_msgs/OccupancyGrid.h"
#include "PlaneStateSpace.h"

class OccupancyMap: public RRT::PlaneStateSpace<Coordinates>{
public:
	OccupancyMap();
	OccupancyMap(const nav_msgs::OccupancyGrid::ConstPtr& msg);
	OccupancyMap(unsigned int width, unsigned int height, float resolution, std::vector<signed char> data);
	//~OccupancyMap();
	Coordinates convertIndex2Coordinate(int i);
	unsigned long convertCoordinate2Index(Coordinates coord) const;

	// SETTERS
	void setInflationRadius(float r){inflationRadius = r;};

	// GETTERS
	unsigned int getWidth(){return _width;}
	unsigned int getHeight(){return _height;}
	float getResolution(){return resolution;}
	std::vector<signed char> & getData(){return data;}
	unsigned long size(){return _size;}
	float getInflationRadius(){return inflationRadius;}

	// ACESS
	signed char operator[](unsigned long i) const;
	signed char operator[](Coordinates coord) const;
	std::vector<Coordinates> & obstacles(){return newObstacles;}

	// RRT
	Coordinates randomState() const{return PlaneStateSpace::randomState();}
	Coordinates intermediateState(const Coordinates& source, const Coordinates& target, float stepSize) const{return PlaneStateSpace::intermediateState(source, target, stepSize);}
	double distance(const Coordinates& from, const Coordinates& to) const{return PlaneStateSpace::distance(from,to);}
	float width() const {return PlaneStateSpace::width();}
	float height() const {return PlaneStateSpace::height();}

	Coordinates intermediateState(const Coordinates& source, const Coordinates& target, float minStepSize, float maxStepSize) const;
	bool stateValid(const Coordinates& pt)const;
	bool transitionValid(const Coordinates& from, const Coordinates& to) const;
	float nearestObstacleDist(const Coordinates& state, float maxDist) const ;

	// AUX
	Coordinates nearestClearGoal(Coordinates& origin, Coordinates & goal);

private:
	unsigned long _size;
	unsigned int _width;
	unsigned int _height;
	float resolution;
	std::vector<signed char> data;
	std::vector<Coordinates> newObstacles;
	float inflationRadius;
};


#endif
