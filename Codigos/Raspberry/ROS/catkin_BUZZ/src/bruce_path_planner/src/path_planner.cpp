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

  ros::Publisher pathPub = n.advertise<nav_msgs::Path>("map_path_planned",1000);
  ros::Publisher routeOkPub = n.advertise<std_msgs::Bool>("route_ok",1000);

  pathMsg.header.seq = 0;
  pathMsg.header.stamp = ros::Time::now();
  pathMsg.header.frame_id = "map";
  int seq = -1;

  ros::Rate loop_rate(10);

  while (ros::ok()){
    loop_rate.sleep();
    if(doIt){
      double maxCost = 99999999;
      ROS_INFO("START");
      for(unsigned i = 0; i < 3; ++i) {
        RRT::BiRRT<Coordinates> biRRT(_stateSpace);
        biRRT.setStartState(start);
        biRRT.setGoalState(goal);
        biRRT.setStepSize(1);
        biRRT.setGoalBias(0.4);
        biRRT.setMaxIterations(10000);

        bool success = biRRT.run();
        ROS_INFO("Succes: %d",success);
        std::vector<Coordinates> path = biRRT.getPath();

        RRT::SmoothPath<Coordinates>(path, *_stateSpace);

        RRT::SmoothEdges2(path, *_stateSpace);
 
        ROS_INFO("Path size: %lu",path.size());
        
        double cost = 0;
        for(unsigned long i = 1;i<path.size();i++){
          Coordinates aux = path[i]-path[i-1];
          cost += aux.norm();
        }
        if(cost < maxCost && success){
          maxCost = cost;
          pathMsg.poses.clear();
          for(unsigned long i = 0;i<path.size();i++){
            geometry_msgs::PoseStamped aux;
            aux.pose.position.x = path[i].x;
            aux.pose.position.y = path[i].y;
            pathMsg.poses.push_back(aux);
          }
          geometry_msgs::PoseStamped aux;
          aux.pose.position.x = goal.x;
          aux.pose.position.y = goal.y;
          pathMsg.poses.push_back(aux);
        }
      }
      std_msgs::Bool okMsg;
      okMsg.data = true;
      routeOkPub.publish(okMsg);
      doIt = false;
      _stateSpace->obstacles().clear();
      ROS_INFO("STOP");
      seq++;
      pathMsg.header.seq = seq;
      pathMsg.header.stamp = ros::Time::now();
      pathPub.publish(pathMsg);    
    }

    ros::spinOnce();
  }

  return 0;
}

void MapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg){
  ROS_INFO("Map received");

   _stateSpace = std::make_shared<OccupancyMap>(msg);

  ROS_INFO("Map received\n");
}

void TFCallback(const tf2_msgs::TFMessage::ConstPtr& msg){
  for(int i=0; i<msg->transforms.size();i++){
    if(msg->transforms[i].header.frame_id == "map"){
        ROS_INFO("x : %f, y: %f",msg->transforms[i].transform.translation.x,msg->transforms[i].transform.translation.y);
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
  ROS_INFO("RECEIVED REQUEST");
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
    ROS_INFO("Point: (%f,%f)",aux.x,aux.y);
    _stateSpace->obstacles().push_back(aux);
  }
}
