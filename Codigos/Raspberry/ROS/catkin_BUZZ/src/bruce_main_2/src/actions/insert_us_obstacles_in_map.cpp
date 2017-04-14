#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void insert_us_obstacles_in_map(Fsm *fsm, std::vector<std::string> args){
	std::string usNames[] = {"/ultrasound1","/ultrasound2","/ultrasound3","/ultrasound4","/ultrasound5",
                                    "/ultrasound6","/ultrasound7","/ultrasound8","/ultrasound9","/ultrasound10",
                                    "/ultrasound11"};		
	double obstacle_inflation = std::atof(args[0].c_str());
	if(!fsm->info->calculating_route){
		static int seq = 0;
		geometry_msgs::PoseArray arrayMsg;
		arrayMsg.header.seq = seq;
		seq++;
		arrayMsg.header.stamp = ros::Time::now();
		arrayMsg.header.frame_id = "map";
		for (int i = 0; i < NUM_US; ++i){
			if(fsm->info->US[i] < MAX_RANGE-0.1){
				tf::StampedTransform transform;
				try{
					geometry_msgs::Pose poseMsg;
					fsm->info->tfListener->lookupTransform(usNames[i], "/map",  
					ros::Time(0), transform);
					tf::Vector3 us(fsm->info->US[i]+obstacle_inflation,0,0);
					tf::Vector3 usT = transform.inverse()(us);
					
					#ifdef PRINT_ENABLED
						ROS_INFO("%f,%f,%f",usT.x(),usT.y(),usT.z());
					#endif					
					
					poseMsg.position.x = usT.x();
					poseMsg.position.y = usT.y();
					poseMsg.position.z = obstacle_inflation;
					arrayMsg.poses.push_back(poseMsg);
				}catch (tf::TransformException & ex){
					#ifdef PRINT_ENABLED
						ROS_ERROR("%s",ex.what());
					#endif					
				}
				#ifdef PRINT_ENABLED
					ROS_INFO("US[%d] = %f",i+1,fsm->info->US[i]);
				#endif						
			}
		}	
		fsm->info->pubObstacles->publish(arrayMsg);
		ROS_INFO("obstacle_inflation = %f",obstacle_inflation);
	}
}
