#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void insert_camera_readings_in_map	(Fsm *fsm, std::vector<std::string> args){	
	if(!fsm->info->calculating_route){
		float distance = fsm->info->cameraReadDistance;
		float orientation = toRadian(-1.0*fsm->info->cameraReadOrientation);
		float x = distance*std::cos(orientation);
		float y = distance*std::sin(orientation);
		tf::Vector3 cone(x,y,0);
		tf::StampedTransform transform;
		try{
			fsm->info->tfListener->lookupTransform("/camera", "/map",  
					ros::Time(0), transform);
			tf::Vector3 coneInMap = transform.inverse()(cone);
			#ifdef PRINT_ENABLED
				ROS_INFO("%f,%f,%f",coneInMap.x(),coneInMap.y(),coneInMap.z());
			#endif
			fsm->info->currentMapGoal.x = coneInMap.x();
			fsm->info->currentMapGoal.y = coneInMap.y();
		}catch (tf::TransformException & ex){
			#ifdef PRINT_ENABLED
				ROS_ERROR("%s",ex.what());
			#endif
		}
	}
}
