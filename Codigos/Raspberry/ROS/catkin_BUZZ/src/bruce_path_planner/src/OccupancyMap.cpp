#include "OccupancyMap.h"
#include <algorithm>
#include "ros/ros.h"


template <typename T>
bool inRange(T n, T min, T max) {
    return (n >= min) && (n <= max);
}

OccupancyMap::OccupancyMap():
	PlaneStateSpace(0,0){
	this->_width = 0;
	this->_height = 0;
	this->resolution = 0;
	this->_size = _width*_height;
	this->data = std::vector<signed char>();
           this->inflationRadius = 0;
}

OccupancyMap::OccupancyMap(const nav_msgs::OccupancyGrid::ConstPtr& msg):
	PlaneStateSpace(msg->info.width*msg->info.resolution,msg->info.height*msg->info.resolution){
	this->_width = msg->info.width;
	this->_height = msg->info.height;
	this->resolution = msg->info.resolution;
	this->_size = _width*_height;
	this->data = msg->data;
           this->inflationRadius = 0;    
}

OccupancyMap::OccupancyMap(unsigned int width, unsigned int height, float resolution, std::vector<signed char> data):
	PlaneStateSpace(width*resolution,height*resolution){
	this->_width = width;
	this->_height = height;
	this->resolution = resolution;
	this->_size = _width*_height;
	this->data = data;
           this->inflationRadius = 0;    
}

signed char OccupancyMap::operator[](unsigned long i) const{ 
	if(i >_size){
		return data[_size-1];
	}else{
		return data[i];
	}
}

signed char OccupancyMap::operator[](Coordinates coord) const{
	unsigned long i = convertCoordinate2Index(coord);
	return (*this)[i];
}


Coordinates OccupancyMap::convertIndex2Coordinate(int i){
  Coordinates coord;
  coord.x = (i%_width)*resolution;
  coord.y = (i/_width)*resolution;
  return coord;
}

unsigned long OccupancyMap::convertCoordinate2Index(Coordinates coord) const{
  unsigned long x = coord.x/resolution;
  unsigned long y = coord.y/resolution;
  unsigned long value = _width*y+x;
  return value;
}

//RRT

bool OccupancyMap::stateValid(const Coordinates& pt)const{
    bool inbounds = PlaneStateSpace::stateValid(pt);
    float distToObs = nearestObstacleDist(pt,1);
    signed char mapPoint = (*this)[pt];
    bool nearObstacle = distToObs < 1;
    bool notObstable = (mapPoint == 0) ;

    for (int i = 0; i < newObstacles.size(); ++i){
        Coordinates aux = pt - newObstacles[i];
        if(aux.norm() < inflationRadius){
            notObstable = false;
        }
    }

    return inbounds && notObstable && !nearObstacle;
}

Coordinates OccupancyMap::intermediateState(const Coordinates& source,
                                           const Coordinates& target,
                                           float minStepSize,
                                           float maxStepSize) const {

    Coordinates delta = target - source;
    delta = delta / delta.norm();  //  unit vector
    float dist = nearestObstacleDist(source, maxStepSize * 2);

    float stepSize = (dist / maxStepSize) * minStepSize;  // scale based on how far we are from obstacles
    if (stepSize > maxStepSize) stepSize = maxStepSize;
    if (stepSize < minStepSize) stepSize = minStepSize;

    Coordinates val = source + delta * stepSize;
    return val;
}

float OccupancyMap::nearestObstacleDist(const Coordinates& state,
                                        float maxDist) const {
    // x and y are the indices of the cell that state is located in
    float x = state.x;
    float y = state.y;
    int xSearchRad = maxDist;
    int ySearchRad = maxDist;
    // here we loop through the cells around (x,y) to find the minimum distance
    // of
    // the point to the nearest obstacle
    for (float i = x - xSearchRad; i <= x + xSearchRad; i+=resolution) {
        for (float j = y - ySearchRad; j <= y + ySearchRad; j+=resolution) {
        	signed char mapPoint = (*this)[Coordinates(i,j)];
           bool obs = (mapPoint != 0);
           for (int i = 0; i < newObstacles.size(); ++i){
                Coordinates aux = Coordinates(i,j) - newObstacles[i];
                if(aux.norm() < inflationRadius){
                    obs = true;
                }
           }           
            if (obs) {
                float xDist = (x - i);
                float yDist = (y - j);
                float dist = sqrtf(powf(xDist, 2) + powf(yDist, 2));
                if (dist < maxDist) {
                    maxDist = dist;
                }
            }
        }
    }

    // the boundaries of the grid count as obstacles
    maxDist = std::min(maxDist, state.x);             // left boundary
    maxDist = std::min(maxDist, width() - state.x);   // right boundary
    maxDist = std::min(maxDist, state.y);             // top boundary
    maxDist = std::min(maxDist, height() - state.y);  // bottom boundary

    return maxDist;
}

bool OccupancyMap::transitionValid(const Coordinates& from,
                                     const Coordinates& to) const {
    //  make sure we're within bounds
    if (!stateValid(to)) return false;

    Coordinates delta = to - from;

    //  get the corners of this segment in integer coordinates.  This limits our
    //  intersection test to only the boxes in that square
    float x1 = from.x, y1 = from.y;
    float x2 = to.x, y2 = to.y;

    //  order ascending
    if (x1 > x2) std::swap<float>(x1, x2);
    if (y1 > y2) std::swap<float>(y1, y2);

    float gridSqWidth  = 10*resolution;
    float gridSqHeight = 10*resolution;

    //  check all squares from (x1, y1) to (x2, y2)
    for (float x = x1; x <= x2; x+=resolution) {
        for (float y = y1; y <= y2; y+=resolution) {
        	signed char mapPoint = (*this)[Coordinates(x,y)];
           bool obs = (mapPoint != 0);
           for (int i = 0; i < newObstacles.size(); ++i){
                Coordinates aux = Coordinates(x,y) - newObstacles[i];
                if(aux.norm() < inflationRadius){
                    obs = true;
                }
           }
            if (obs) {
                //  there's an obstacle here, so check for intersection

                //  the corners of this obstacle square
                Coordinates ulCorner(x, y);
                Coordinates brCorner(x + gridSqWidth, y + gridSqHeight);

                if (delta.x != 0) {
                    /**
                     * Find slope and y-intercept of the line passing through
                     * @from and
                     * @to.
                     * y1 = m*x1+b
                     * b = y1-m*x1
                     */
                    float slope = delta.y / delta.x;
                    float b = to.y - to.x * slope;

                    /*
                     * First check intersection with the vertical segments of
                     * the box.
                     * Use y=mx+b for the from-to line and plug in the x value
                     * for each
                     * wall
                     * If the corresponding y-value is within the y-bounds of
                     * the vertical
                     * segment, it's an intersection.
                     */
                    float yInt = slope * ulCorner.x + b;
                    if (inRange<float>(yInt, ulCorner.y, brCorner.y))
                        return false;
                    yInt = slope * brCorner.x + b;
                    if (inRange<float>(yInt, ulCorner.y, brCorner.y))
                        return false;

                    /*
                     * Check intersection with horizontal sides of box
                     * y = k;
                     * y = mx+b;
                     * mx+b = k;
                     * mx = k - b;
                     * (k - b) / m = x;  is x within the horizontal range of the
                     * box?
                     */
                    if (slope == 0) return false;
                    float xInt = (ulCorner.y - b) / slope;
                    if (inRange<float>(xInt, ulCorner.x, brCorner.x))
                        return false;
                    xInt = (brCorner.y - b) / slope;
                    if (inRange<float>(xInt, ulCorner.x, brCorner.x))
                        return false;
                } else {
                    //  vertical line - slope undefined

                    //  see if it's within the x-axis bounds of this obstacle
                    //  box
                    if (inRange<float>(from.x, ulCorner.x, brCorner.x)) {
                        //  order by y-value
                        //  note: @lower has a smaller value of y, but will
                        //  appear higher
                        //  visually on the screen due to qt's coordinate layout
                        Coordinates lower(from);
                        Coordinates higher(to);
                        if (higher.y < lower.y)
                            std::swap<Coordinates>(lower, higher);

                        //  check for intersection based on y-values
                        if (lower.y < ulCorner.y &&
                            higher.y > ulCorner.y)
                            return false;
                        if (lower.y < brCorner.y &&
                            higher.y > brCorner.y)
                            return false;
                    }
                }
            }
        }
    }

    return true;
}
