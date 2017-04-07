#include "ros/ros.h"
#include "fsm.h"
#include "fsmparser.h"
#include "states.h"
#include "bruce_main/vitals.h"

robot_information info;

void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg);
void OdomOkCallback(const std_msgs::Bool::ConstPtr& msg);
void RouteOkCallback(const std_msgs::Bool::ConstPtr& msg);
void ConeEncontradoCallback(const std_msgs::Bool::ConstPtr& msg);
void startInfo(robot_information & info);
void OriginCallback(const geometry_msgs::Point32::ConstPtr& msg);
void PathCallback(const nav_msgs::Path::ConstPtr& msg);
void UltrassomCallback(const sensor_msgs::Range::ConstPtr& msg);

bool route_received = false;

int main(int argc, char **argv){
  ros::init(argc, argv, "main");

  std::string filename;

  if(argc == 2){
    filename = argv[1];
  }else{
    ROS_ERROR("Missing description file argument");
    return -1;
  }
  std::vector<fsm_parser_state> fsm_states;
  startStates(fsm_states);
  startInfo(info);
  struct fsm_object fsm;
  fsm_init(&fsm);
  fsm.info = &info;

  try{
      parseFile(filename,fsm_states,fsm);
      
      ros::NodeHandle n;

      ros::Subscriber subOdom = n.subscribe("odom", 1000, OdomCallback);
      ros::Subscriber subOdomOk = n.subscribe("odom_ok", 1000, OdomOkCallback); 
      ros::Subscriber subRouteOk = n.subscribe("route_ok", 1000, RouteOkCallback);
      ros::Subscriber subOrigin = n.subscribe("origin", 1000, OriginCallback);
      ros::Subscriber subPath = n.subscribe("map_path_planned",1000,PathCallback);
      ros::Subscriber subConeEncontrado = n.subscribe("cone_encontrado",1000,ConeEncontradoCallback);
      ros::Subscriber subUS1 = n.subscribe("ultrasound1",1000,UltrassomCallback);
      ros::Subscriber subUS2 = n.subscribe("ultrasound2",1000,UltrassomCallback);
      ros::Subscriber subUS3 = n.subscribe("ultrasound3",1000,UltrassomCallback);
      ros::Subscriber subUS4 = n.subscribe("ultrasound4",1000,UltrassomCallback);
      ros::Subscriber subUS5 = n.subscribe("ultrasound5",1000,UltrassomCallback);
      ros::Subscriber subUS6 = n.subscribe("ultrasound6",1000,UltrassomCallback);
      ros::Subscriber subUS7 = n.subscribe("ultrasound7",1000,UltrassomCallback);
      ros::Subscriber subUS8 = n.subscribe("ultrasound8",1000,UltrassomCallback);
      ros::Subscriber subUS9 = n.subscribe("ultrasound9",1000,UltrassomCallback);
      ros::Subscriber subUS10 = n.subscribe("ultrasound10",1000,UltrassomCallback);
      ros::Subscriber subUS11 = n.subscribe("ultrasound11",1000,UltrassomCallback);
      tf::TransformListener tfListener;

      ros::Publisher pathPub = n.advertise<nav_msgs::Path>("path_planned",1000);
      ros::Publisher pubEnableFollowPath = n.advertise<std_msgs::Bool>("enable_follow_path",1000);
      ros::Publisher pubRequestPath = n.advertise<geometry_msgs::Point32>("path_request",1000); 
      ros::Publisher pubMapBLCoordinate = n.advertise<geometry_msgs::Point32>("map_bl_coord",1000); 
      ros::Publisher pubObstacles = n.advertise<geometry_msgs::PoseArray>("new_obstacles",1000);
      
      info.n = &n;
      info.pubRequestPath = & pubRequestPath;
      info.pubMapBLCoordinate = & pubMapBLCoordinate;
      info.pubPath = & pathPub;
      info.pubEnableFollowPath = & pubEnableFollowPath;
      info.pubObstacles = & pubObstacles;
      info.tfListener = & tfListener;
      
      ros::Rate loop_rate(30);

      sleep(1);

      while (ros::ok()){
        loop_rate.sleep();

        // start the main FSM loop
        bool stop = fsm_main(&fsm);
        if(stop){
          break;
        }
        ros::spinOnce();
      }      
    }catch(char const * aux){
      ROS_ERROR("%s",aux);
    }

  return 0;
}

void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
  info.pose = msg->pose.pose;
}

void OdomOkCallback(const std_msgs::Bool::ConstPtr& msg){
  info.position_is_valid = msg->data;
}

void RouteOkCallback(const std_msgs::Bool::ConstPtr& msg){
  route_received = msg->data;
  ROS_INFO("RECEBI %d", msg->data);
}

void ConeEncontradoCallback(const std_msgs::Bool::ConstPtr& msg){
  info.cone_encontrado = msg->data;
  ROS_INFO("O cone foi encontrado %d", msg->data);  
}

void startInfo(robot_information & info){
  info.position_is_valid = false;
  info.route_calculated = false;
  info.cone_encontrado = false;
  info.pose = geometry_msgs::Pose();
  info.origin.lat = 0;
  info.origin.lng = 0;
  info.bottomLeft.lat = 0;
  info.bottomLeft.lng = 0;  
}

void OriginCallback(const geometry_msgs::Point32::ConstPtr& msg){
  info.origin.lat = msg->x;
  info.origin.lng = msg->y; 
}

void PathCallback(const nav_msgs::Path::ConstPtr& msg){
  nav_msgs::Path pathMsg;

  pathMsg.header.seq = 0;
  pathMsg.header.stamp = ros::Time::now();
  pathMsg.header.frame_id = "odom";  

  NEDCoord origin = GPS2NED(info.origin,info.bottomLeft);
  info.path.clear();
  for(int i =0;i<msg->poses.size();i++){
    geometry_msgs::PoseStamped aux;
    double map_x = msg->poses[i].pose.position.y;
    double map_y = msg->poses[i].pose.position.x;
    aux.pose.position.x = map_x-origin.x;
    aux.pose.position.y = map_y-origin.y;
    NEDCoord nedAux = {aux.pose.position.x,aux.pose.position.y}; 
    info.path.push_back(nedAux);
    pathMsg.poses.push_back(aux);
  }
  if(route_received){
      info.pubPath->publish(pathMsg);
      info.route_calculated = true;
      ROS_INFO("RECEBI rota");
      route_received = false; 
  }
}

void UltrassomCallback(const sensor_msgs::Range::ConstPtr& msg){
  std::string usNames[] = {"/ultrasound1","/ultrasound2","/ultrasound3","/ultrasound4","/ultrasound5",
                                        "/ultrasound6","/ultrasound7","/ultrasound8","/ultrasound9","/ultrasound10",
                                        "/ultrasound11"};
  for(int i=0; i<NUM_US;i++){
    if(usNames[i] == msg->header.frame_id){
      info.US[i] = msg->range;
    }
  }
}

double toRadian(double degree){
  return (degree*PI/180.0);
}


ECEFCoord GPS2ECEF(GPSCoord gpoint){
  float a = 6378137;
  float b = 6356752.31424518;
  float f = (a-b)/a;
  float e = std::sqrt(f*(2.0-f));
  float sinLat = std::sin(toRadian(gpoint.lat));
  float cosLat = std::cos(toRadian(gpoint.lat));
  float sinLng = std::sin(toRadian(gpoint.lng));
  float cosLng = std::cos(toRadian(gpoint.lng));
  float N = a/(std::sqrt(1-(e*e*sinLat*sinLat))); 

  ECEFCoord ecefPoint;

  ecefPoint.x = (N+gpoint.alt)*cosLat*cosLng;
  ecefPoint.y = (N+gpoint.alt)*cosLat*sinLng;
  ecefPoint.z = (N*(1-e*e)+gpoint.alt)*sinLat; 
  return ecefPoint;
}

NEDCoord GPS2NED(GPSCoord gpoint ,GPSCoord ref){
  
  
  ECEFCoord ecefPoint = GPS2ECEF(gpoint);
  ECEFCoord refEcefPoint = GPS2ECEF(ref);
  
  NEDCoord nedPoint,aux;
  
  double sLaR = std::sin(toRadian(ref.lat));
  double cLaR = std::cos(toRadian(ref.lat));
  double sLoR = std::sin(toRadian(ref.lng));
  double cLoR = std::cos(toRadian(ref.lng));

  aux.x = ecefPoint.x-refEcefPoint.x;
  aux.y = ecefPoint.y-refEcefPoint.y;
  aux.z = ecefPoint.z-refEcefPoint.z;

  nedPoint.x = -sLaR*cLoR*aux.x  - sLaR*sLoR*aux.y + cLaR*aux.z;
  nedPoint.y = -sLoR*aux.x          + cLoR*aux.y;
  nedPoint.z = -cLaR*cLoR*aux.x  - cLaR*sLoR*aux.y - sLaR*aux.z;

  return nedPoint;
}
