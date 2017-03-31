#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point32.h>
#include <std_msgs/Bool.h>
#include <cstdlib>

int main(int argc, char** argv){
  ros::init(argc, argv, "odometry_publisher");

  double x = 0.0;
  double y = 0.0;
  double rx = 0.0;
  double ry = 0.0;
  double rz = 0.0;
  double rw = 1.0;
  double lat = 0.0;
  double lng = 0.0;

  for(int i=0; i<argc;i++){
    ROS_INFO("%d, %s",i,argv[i]);
    if(i==1){
      x = std::atof(argv[i]);
    }else if(i==2){
      y = std::atof(argv[i]);
    }else if(i==3){
      rx = std::atof(argv[i]);
    }else if(i==4){
      ry = std::atof(argv[i]);
    }else if(i==5){
      rz = std::atof(argv[i]);
    }else if(i==6){
      rw = std::atof(argv[i]);
    }else if(i==7){
      lat = std::atof(argv[i]);
    }else if(i==8){
      lng = std::atof(argv[i]);
    }
  }

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  ros::Publisher origin_pub = n.advertise<geometry_msgs::Point32>("origin", 50);
  ros::Publisher odom_ok = n.advertise<std_msgs::Bool>("odom_ok", 50);
  

  geometry_msgs::Point32 origin;
  std_msgs::Bool odomOK;
  odomOK.data = true;

  origin.x = lat;
  origin.y = lng;

  double vx = 0;
  double vy = 0.0;
  double vth = 0.0;

  ros::Time current_time;
  current_time = ros::Time::now();

  ros::Rate r(60);
  while(n.ok()){

    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    x+= vx/60.0;

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;

    odom.pose.pose.orientation.x = rx;
    odom.pose.pose.orientation.y = ry;
    odom.pose.pose.orientation.z = rz;    
    odom.pose.pose.orientation.w = rw;
    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;
    ROS_INFO("%f, %f",x,y);
    //publish the message
    odom_pub.publish(odom);
    origin_pub.publish(origin);
    odom_ok.publish(odomOK);
    r.sleep();
  }
}
