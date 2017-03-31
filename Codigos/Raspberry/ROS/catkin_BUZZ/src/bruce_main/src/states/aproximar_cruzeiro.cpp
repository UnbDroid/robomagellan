#include "fsm.h"
#include "states.h"
#include "ros/ros.h"

double distanceFromLineToPoint(NEDCoord,NEDCoord,NEDCoord);

double distanceFromSegmentToPoint(NEDCoord P1 ,NEDCoord P2,NEDCoord P0);

void aproximar_cruzeiro(struct fsm_object *obj, int val,void **arg){
	static std::vector<arg_type> args;
	static float obstacle_range;
	static float max_dist_from_route;
	static float wait_recalculate_time;
	static std::vector<std::string> next_states;
	static std::string recalculate_state;
	static std::string avoid_obstacle_state;
	static bool first_time =true;
	static bool new_iteration = true;
	static std::time_t lastPathPlanned;
	if(first_time){
		std::time(&lastPathPlanned);
		processArgs(args,val,arg);
		first_time = false;
		if(args[0].type != SINGLE || args[1].type != SINGLE || args[2].type != SINGLE || args[3].type != SINGLE || args[4].type != SINGLE){
			throw("Panic");
		}
		obstacle_range = std::stof(args[0].single.c_str());
		max_dist_from_route = std::stof(args[1].single.c_str());
		wait_recalculate_time = std::stof(args[2].single.c_str());
		recalculate_state = args[3].single;
		avoid_obstacle_state = args[4].single;
		if(args[5].type == SINGLE){
			next_states.push_back(args[5].single);
		}else{
			for (int i = 0; i < args[5].multiple.size(); ++i){
				next_states.push_back(args[5].multiple[i]);
			}
		}
	}

	if(new_iteration){
		ROS_INFO("Entrando no aproximar_cruzeiro");
		std_msgs::Bool msg;
		msg.data = true;
		obj->info->pubEnableFollowPath->publish(msg);
		new_iteration = false;
	}
	ROS_INFO("%f %f ",obstacle_range,max_dist_from_route);
	double min_dist = 9999999;
	for(int i=1;i < obj->info->path.size();i++){
		NEDCoord P0 = {obj->info->pose.position.x,obj->info->pose.position.y};
		double projection = distanceFromSegmentToPoint(obj->info->path[i-1],obj->info->path[i],P0);
		if(projection < min_dist){
			min_dist = projection;
		}
	}
	ROS_INFO("Min dist: %f",min_dist);

	std::time_t now;
	std::time(&now);
	ROS_INFO("%f, %f",wait_recalculate_time,std::difftime(now,lastPathPlanned));
	for (int i = 3; i < 8; ++i){
		if(std::difftime(now,lastPathPlanned) > wait_recalculate_time && obj->info->US[i] < obstacle_range){
			ROS_INFO("OBSTACULO NO CAMINHO");
			fsm_to_state(obj,avoid_obstacle_state);
			std::time(&lastPathPlanned);
			break;
		}
		ROS_INFO("US[%d] = %f",i+1,obj->info->US[i]);
	}
	if(min_dist > max_dist_from_route){
		ROS_INFO("RECALCULAR ROTA");
		fsm_to_state(obj,recalculate_state);
		new_iteration = true;	
	}
	if(obj->info->cone_encontrado){
		static int run_iterator = 0;
		obj->info->cone_encontrado = false;
		ROS_INFO("O CONE FOI ENCONTRADO");
		std_msgs::Bool msg;
		msg.data = false;
		obj->info->pubEnableFollowPath->publish(msg);
		new_iteration = true;	
		fsm_to_state(obj,next_states[run_iterator]);
		run_iterator++;
	}

}

double distanceFromSegmentToPoint(NEDCoord P1 ,NEDCoord P2,NEDCoord P0){
	double deltaXa = P2.x-P1.x;
	double deltaYa = P2.y-P1.y;
	double deltaXb = P0.x-P1.x;
	double deltaYb = P0.y-P1.y;
	double t1 = deltaXa*deltaXb;
	double t2 = deltaYa*deltaYb;
	double b1 = deltaXa*deltaXa;
	double b2 = deltaYa*deltaYa;
	double t = t1+t2;
	double b = b1+b2;
	double gama = t/b;
	if(0.0 <= gama && gama <= 1){
		double at1 = deltaYa*P0.x;
		double at2 = deltaXa*P0.y;
		double at3 = P2.x*P1.y;
		double at4 = P2.y*P1.x;
		double at = std::abs(at1-at2+at3-at4);
		double ab = std::sqrt(b);
		return at/ab;
	}
	double dist1 = std::sqrt(deltaXb*deltaXb+deltaYb*deltaYb);
	double ad1 = P2.x-P0.x;
	double ad2 = P2.y-P0.y;
	double dist2 = std::sqrt(ad1*ad1+ad2*ad2);
	if(dist1>dist2){
		return dist2;
	}else{
		return dist1;
	}
}


double distanceFromLineToPoint(NEDCoord P1 ,NEDCoord P2,NEDCoord P0){
	double deltaX = P2.x-P1.x;
	double deltaY = P2.y-P1.y;
	double t1 = deltaY*P0.x;
	double t2 = deltaX*P0.y;
	double t3 = P2.x*P1.y;
	double t4 = P2.y*P1.x;
	double t = std::abs(t1-t2+t3-t4);
	double b1 = deltaY*deltaY;
	double b2 = deltaX*deltaX;
	double b = std::sqrt(b1+b2);
	return t/b;
}
