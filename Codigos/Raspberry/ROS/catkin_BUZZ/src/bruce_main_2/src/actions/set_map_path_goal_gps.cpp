
#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void set_map_path_goal_gps(Fsm *fsm, std::vector<std::string> args){
	if(!fsm->info->calculating_route){
		GPSCoord gpsGoal ={std::atof(args[0].c_str()), std::atof(args[1].c_str())};
		NEDCoord nedGoal = GPS2NED(gpsGoal,fsm->info->bottomLeft);
		NEDCoord originInMap = GPS2NED(fsm->info->origin,fsm->info->bottomLeft);
		fsm->info->originInMap.x = originInMap.y;
		fsm->info->originInMap.y = originInMap.x;
		float map_x = nedGoal.y;
		float map_y = nedGoal.x;
		fsm->info->currentMapGoal.x = map_x;
		fsm->info->currentMapGoal.y = map_y;
	}
}
