#pragma once
#include <cmath>

class Coordinates{
public:
	Coordinates(){x=0;y=0;}
	Coordinates(float x, float y):x(x),y(y){}
	Coordinates operator+ (const Coordinates& other)const {
		return Coordinates(x+other.x,y+other.y);
	}
	Coordinates operator- (const Coordinates& other)const {
		return Coordinates(x-other.x,y-other.y);
	}
	Coordinates operator/ (const float& other)const {
		return Coordinates(x/other,y/other);
	}
	Coordinates operator* (const float& other)const {
		return Coordinates(x*other,y*other);
	}	
	float norm(){return std::sqrt(x*x+y*y);}
	float x,y;
};
