#include "ros/ros.h"
#include "fsm.h"
#include "parser/fsmparser.h"

robot_information info;

void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg);
void OdomOkCallback(const std_msgs::Bool::ConstPtr& msg);
void RouteOkCallback(const std_msgs::Bool::ConstPtr& msg);
void ConeEncontradoCallback(const std_msgs::Bool::ConstPtr& msg);
void OriginCallback(const geometry_msgs::Point32::ConstPtr& msg);
void PathCallback(const nav_msgs::Path::ConstPtr& msg);
void UltrassomCallback(const sensor_msgs::Range::ConstPtr& msg);
void CameraPositionCallback(const geometry_msgs::Point32::ConstPtr& msg);
void SensorToqueCallback(const std_msgs::Bool::ConstPtr& msg);
void BotaoPretoCallback(const std_msgs::Bool::ConstPtr& msg);
void BotaoVerdeCallback(const std_msgs::Bool::ConstPtr& msg);

void startInfo(robot_information & info);

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
  Fsm fsm;
  fsm_init(&fsm);
  startInfo(info);
  fsm.info = &info;

  try{
      parseFile(filename,fsm);
      
      ros::NodeHandle n;

      /* Subscribers */
      ros::Subscriber subOdom = n.subscribe("odom", 1000, OdomCallback);
      ros::Subscriber subOdomOk = n.subscribe("odom_ok", 1000, OdomOkCallback); 
      ros::Subscriber subRouteOk = n.subscribe("route_ok", 1000, RouteOkCallback);
      ros::Subscriber subOrigin = n.subscribe("origin", 1000, OriginCallback);
      ros::Subscriber subPath = n.subscribe("map_path_planned",1000,PathCallback);
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
      ros::Subscriber subCamera = n.subscribe("cone_position",1000,CameraPositionCallback);
      ros::Subscriber subSensorToque = n.subscribe("sensor_toque", 1000, SensorToqueCallback);
      ros::Subscriber subBotaoPreto = n.subscribe("botao_preto", 1000, BotaoPretoCallback);
      ros::Subscriber subBotaoVerde = n.subscribe("botao_verde", 1000, BotaoVerdeCallback);
      tf::TransformListener tfListener;      


      /* Publishers */
      ros::Publisher pathPub = n.advertise<nav_msgs::Path>("path_planned",1000,true);
      ros::Publisher pubEnableFollowPath = n.advertise<std_msgs::Int16>("enable_follow_path",1000,true);
      ros::Publisher pubRequestPath = n.advertise<geometry_msgs::Point32>("path_request",1000,true); 
      ros::Publisher pubMapBLCoordinate = n.advertise<geometry_msgs::Point32>("map_bl_coord",1000,true); 
      ros::Publisher pubObstacles = n.advertise<geometry_msgs::PoseArray>("new_obstacles",1000);
      ros::Publisher pubOriginRequest = n.advertise<std_msgs::Bool>("request_origin",1000);
      ros::Publisher pubVelocity = n.advertise<geometry_msgs::Point32>("velocity",1000);
      ros::Publisher pubFollowCamera = n.advertise<std_msgs::Bool>("follow_camera",1000);

      info.n = &n;
      info.pubRequestPath = & pubRequestPath;
      info.pubMapBLCoordinate = & pubMapBLCoordinate;
      info.pubPath = & pathPub;
      info.pubEnableFollowPath = & pubEnableFollowPath;
      info.pubObstacles = & pubObstacles;
      info.pubOriginRequest = & pubOriginRequest;
      info.pubVelocity = & pubVelocity;
      info.pubFollowCamera = & pubFollowCamera;
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
  //ROS_INFO("Odometry is OK");
}

void RouteOkCallback(const std_msgs::Bool::ConstPtr& msg){
  route_received = msg->data;
  #ifdef PRINT_ENABLED
    ROS_INFO("RECEBI %d", msg->data);
  #endif
}

void startInfo(robot_information & info){
  info.position_is_valid = false;
  info.route_calculated = false;
  info.cone_encontrado = false;
  info.calculating_route = false;
  info.sensor_toque = false;
  info.origin_received = false;
  info.pose = geometry_msgs::Pose();
  info.origin.lat = 0;
  info.origin.lng = 0;
  info.bottomLeft.lat = 0;
  info.bottomLeft.lng = 0;  
}

void OriginCallback(const geometry_msgs::Point32::ConstPtr& msg){
  info.origin_received = true;
  info.origin.lat = msg->x;
  info.origin.lng = msg->y; 
}

void PathCallback(const nav_msgs::Path::ConstPtr& msg){
  static int seq  = -999;
  if(msg->header.seq != seq){
    seq = msg->header.seq;
    nav_msgs::Path pathMsg;

    pathMsg.header.seq = seq;
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
        #ifdef PRINT_ENABLED
          ROS_INFO("RECEBI rota");
        #endif
        route_received = false; 
    }
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

void CameraPositionCallback(const geometry_msgs::Point32::ConstPtr& msg){
	info.cone_encontrado = msg->z;
	if(info.cone_encontrado){
		info.cameraReadDistance = msg->x;	
		info.cameraReadOrientation = msg->y;		
	}
  #ifdef PRINT_ENABLED
    ROS_INFO("O cone foi encontrado %f", msg->z);  
  #endif
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

void SensorToqueCallback(const std_msgs::Bool::ConstPtr& msg){
  info.sensor_toque = msg->data;
}

void BotaoPretoCallback(const std_msgs::Bool::ConstPtr& msg){
  info.botao_preto = msg->data;
}
void BotaoVerdeCallback(const std_msgs::Bool::ConstPtr& msg){
  info.botao_verde = msg->data;
}
