#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "geometry_msgs/PoseArray.h"
#include "nav_msgs/Path.h"
#include "std_msgs/Bool.h"
#include <tf/transform_listener.h>
#include "OccupancyMap.h"
#include "RRT.h"
#include "BiRRT.hpp"
#include "Path.hpp"
#include <string>
#include <sstream>
#define PRINT_ENABLED

OccupancyMap occMap;
std::shared_ptr<OccupancyMap> _stateSpace;

nav_msgs::Path pathMsg;  
tf2_msgs::TFMessage test;

geometry_msgs::PointStamped clickedPoint;

bool doIt = false;

Coordinates start = {0, 0}, goal = {0, 0};


void MapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg);
void TFCallback(const tf2_msgs::TFMessage::ConstPtr& msg);
void ClickedCallback(const geometry_msgs::PointStamped::ConstPtr& msg);
void PathRequestCallback(const geometry_msgs::Point32::ConstPtr& msg);

void NewObstaclesCallback(const geometry_msgs::PoseArray::ConstPtr& msg);

int main(int argc, char **argv){
  ros::init(argc, argv, "path_planner");

  ros::NodeHandle n;

  ros::Subscriber subClicked = n.subscribe("clicked_point", 1000, ClickedCallback);
  ros::Subscriber subTF = n.subscribe("tf", 1000, TFCallback);
  ros::Subscriber sub = n.subscribe("map", 1000, MapCallback);
  ros::Subscriber subPathRequest = n.subscribe("path_request", 1000, PathRequestCallback);
  ros::Subscriber subNewObstacles = n.subscribe("new_obstacles", 1000, NewObstaclesCallback);

  ros::Publisher pathPub = n.advertise<nav_msgs::Path>("map_path_planned",1000,true);
  ros::Publisher routeOkPub = n.advertise<std_msgs::Bool>("route_ok",1000,true);

  pathMsg.header.seq = 0;
  pathMsg.header.stamp = ros::Time::now();
  pathMsg.header.frame_id = "map";
  static float seq = -1;

  ros::Rate loop_rate(10);

  while (ros::ok()){
    loop_rate.sleep();
    if(doIt){
      double maxCost = 99999999;
      #ifdef PRINT_ENABLED
        ROS_INFO("START");
      #endif
       bool goalIsObstacle = (*_stateSpace)[goal] != 0;
       bool startIsObstacle = (*_stateSpace)[start] != 0;
      #ifdef PRINT_ENABLED
        ROS_INFO("Is goal obstacle? %d",goalIsObstacle);
	ROS_INFO("Is start obstacle? %d", startIsObstacle);
      #endif 
      if(startIsObstacle){
	start = _stateSpace->nearestClearGoal(goal,start);
      }
      if(goalIsObstacle){
        goal = _stateSpace->nearestClearGoal(start,goal);
      }


      for(unsigned i = 0; i < 2; ++i) {
        RRT::BiRRT<Coordinates> biRRT(_stateSpace);
        biRRT.setStartState(start);
        biRRT.setGoalState(goal);
        biRRT.setStepSize(0.5);
        biRRT.setGoalBias(0.1);
        biRRT.setMaxIterations(100000);

       

        bool success = biRRT.run();
        #ifdef PRINT_ENABLED
          ROS_INFO("Succes: %d",success);
        #endif
        std::vector<Coordinates> path = biRRT.getPath();

        RRT::SmoothPath<Coordinates>(path, *_stateSpace);

        RRT::SmoothEdges3(path, *_stateSpace);
        //RRT::SmoothEdges2(path, *_stateSpace);
 
        #ifdef PRINT_ENABLED
          ROS_INFO("Path size: %lu",path.size());
        #endif

        double cost = 0;
        for(unsigned long i = 1;i<path.size();i++){
          Coordinates aux = path[i]-path[i-1];
          cost += aux.norm();
        }
        if(cost < maxCost && success){
          maxCost = cost;
          pathMsg.poses.clear();
	  //seq+=1.0;
	  //ROS_INFO("%f",seq);
          for(unsigned long i = 0;i<path.size();i++){
            geometry_msgs::PoseStamped aux;
            aux.pose.position.x = path[i].x;
            aux.pose.position.y = path[i].y;
            //aux.pose.position.z = seq;
	    	//ROS_INFO("%f, %f",seq, aux.pose.position.z); 
	    	pathMsg.poses.push_back(aux);
          }
          if(!goalIsObstacle){
            geometry_msgs::PoseStamped aux;
            aux.pose.position.x = goal.x;
            aux.pose.position.y = goal.y;
	    	//aux.pose.position.z = seq;
            pathMsg.poses.push_back(aux);
          }
        }
      }
      std_msgs::Bool okMsg;
      okMsg.data = true;
      routeOkPub.publish(okMsg);
      doIt = false;
      _stateSpace->obstacles().clear();
      #ifdef PRINT_ENABLED
        ROS_INFO("STOP");
      #endif
      // seq++;
      //pathMsg.header.seq = seq;
      pathMsg.header.stamp = ros::Time::now();
      pathPub.publish(pathMsg);    
    }
    //ROS_INFO("%f",seq);
    //pathPub.publish(pathMsg);
    ros::spinOnce();
  }

  return 0;
}

void MapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg){
  #ifdef PRINT_ENABLED
    ROS_INFO("Map received");
  #endif
   _stateSpace = std::make_shared<OccupancyMap>(msg);
  #ifdef PRINT_ENABLED
    ROS_INFO("Map received\n");
  #endif
}

void TFCallback(const tf2_msgs::TFMessage::ConstPtr& msg){
  for(int i=0; i<msg->transforms.size();i++){
    if(msg->transforms[i].header.frame_id == "map"){
      #ifdef PRINT_ENABLED
        //ROS_INFO("x : %f, y: %f",msg->transforms[i].transform.translation.x,msg->transforms[i].transform.translation.y);
      #endif
        start.x = msg->transforms[i].transform.translation.x;
        start.y = msg->transforms[i].transform.translation.y;
    }
  }
}

void ClickedCallback(const geometry_msgs::PointStamped::ConstPtr& msg){
  goal.x = msg->point.x;
  goal.y = msg->point.y;
  doIt = true;
}

void PathRequestCallback(const geometry_msgs::Point32::ConstPtr& msg){
  #ifdef PRINT_ENABLED
    ROS_INFO("RECEIVED REQUEST");
  #endif
  goal.x = msg->x;
  goal.y = msg->y;
  doIt = true;
}

void NewObstaclesCallback(const geometry_msgs::PoseArray::ConstPtr& msg){
  if(msg->poses.size() > 0){
    _stateSpace->setInflationRadius(msg->poses[0].position.z);
  }
  for (int i = 0; i < msg->poses.size(); ++i){
    Coordinates aux = {(float)msg->poses[i].position.x,(float)msg->poses[i].position.y};
    #ifdef PRINT_ENABLED
      //ROS_INFO("Point: (%f,%f)",aux.x,aux.y);
    #endif
    _stateSpace->obstacles().push_back(aux);
  }
}
