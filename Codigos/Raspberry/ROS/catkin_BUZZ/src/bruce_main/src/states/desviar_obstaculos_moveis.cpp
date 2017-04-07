#include "fsm.h"
#include "states.h"
#include "ros/ros.h"
#include <ctime>

void desviar_obstaculos_moveis(struct fsm_object *obj, int val,void **arg){
	static std::vector<arg_type> args;
	static bool first_time =true;
	static bool new_iteration = true;
	static float obstacle_inflation = 0;
	static int run_iterator = 0;
	std::string usNames[] = {"/ultrasound1","/ultrasound2","/ultrasound3","/ultrasound4","/ultrasound5",
                                    "/ultrasound6","/ultrasound7","/ultrasound8","/ultrasound9","/ultrasound10",
                                    "/ultrasound11"};	
	if(first_time){
		processArgs(args,val,arg);
		if(args[0].type != SINGLE)
			throw("Setup next_state must be a single argument!");
		obstacle_inflation = std::atof(args[0].single.c_str());
		first_time = false;
	}
	
	if(new_iteration){
		geometry_msgs::PoseArray arrayMsg;
		arrayMsg.header.seq = run_iterator;
		arrayMsg.header.stamp = ros::Time::now();
		arrayMsg.header.frame_id = "map";
		for (int i = 0; i < NUM_US; ++i){
			if(obj->info->US[i] < MAX_RANGE-0.1){
				tf::StampedTransform transform;
				try{
					geometry_msgs::Pose poseMsg;
					obj->info->tfListener->lookupTransform(usNames[i], "/map",  
					ros::Time(0), transform);
					tf::Vector3 us(obj->info->US[i]+obstacle_inflation,0,0);
					tf::Vector3 usT = transform.inverse()(us);
					ROS_INFO("%f,%f,%f",usT.x(),usT.y(),usT.z());
					poseMsg.position.x = usT.x();
					poseMsg.position.y = usT.y();
					poseMsg.position.z = obstacle_inflation;
					arrayMsg.poses.push_back(poseMsg);
				}catch (tf::TransformException & ex){
				      ROS_ERROR("%s",ex.what());
				}
				ROS_INFO("US[%d] = %f",i+1,obj->info->US[i]);
			}
		}	
		obj->info->pubObstacles->publish(arrayMsg);
		ROS_INFO("obstacle_inflation = %f",obstacle_inflation);
		new_iteration = false;
		geometry_msgs::Point32 msg;

		msg.x = obj->info->currentMapGoal.x;
		msg.y = obj->info->currentMapGoal.y;		
		obj->info->pubRequestPath->publish(msg);
		ROS_INFO("Requesting (%f,%f) ",obj->info->currentMapGoal.x,obj->info->currentMapGoal.y);
		ROS_INFO("Origin in map (%f,%f)",obj->info->originInMap.x,obj->info->originInMap.y);

	}

	//ROS_INFO("(%f, %f), %s\n",x_coordinates[run_iterator],y_coordinates[run_iterator],next_states[run_iterator].c_str());
	if(obj->info->route_calculated){
		fsm_return_last_state(obj);
		obj->info->route_calculated = false;
		new_iteration = true;
		run_iterator++;
	}
}

