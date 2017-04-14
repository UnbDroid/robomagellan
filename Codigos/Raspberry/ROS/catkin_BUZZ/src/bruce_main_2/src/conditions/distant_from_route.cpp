#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool distant_from_route(Fsm *fsm, std::vector<std::string>args){
	float distance = std::atof(args[0].c_str());
	
	#ifdef PRINT_ENABLED
		ROS_INFO("%f",distance);
	#endif	
	double min_dist = 9999999;
	NEDCoord P0 = {fsm->info->pose.position.x,fsm->info->pose.position.y};
	for(int i=1;i < fsm->info->path.size();i++){
		double projection = distanceFromSegmentToPoint(fsm->info->path[i-1],fsm->info->path[i],P0);
		if(projection < min_dist){
			min_dist = projection;
		}
	}
	#ifdef PRINT_ENABLED
		ROS_INFO("Pos atual: %f,%f",P0.x,P0.y);
		ROS_INFO("Min dist: %f",min_dist);
	#endif
	if(min_dist > distance){
		return true;
	}	
	return false;
}
