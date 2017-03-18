#include <ros/ros.h>
#include <tf/transform_broadcaster.h>



int main(int argc, char** argv){
  ros::init(argc, argv, "bruce_tf_broadcaster");

  ros::Time time;


  tf::TransformBroadcaster br;

  tf::Transform transformUS1(tf::Quaternion(0,0,1,1),tf::Vector3(0.1,0.1,0.2));

  tf::Transform transformUS2(tf::Quaternion(0,0,-1,1),tf::Vector3(0.1,-0.1,0.2));

  tf::Transform transformUS3(tf::Quaternion(0,0,1,1),tf::Vector3(0.15,0.1,0.2));

  tf::Transform transformUS4(tf::Quaternion(0,0,-1,1),tf::Vector3(0.15,-0.1,0.2));

  ros::Rate loop_rate(10);

  ros::NodeHandle node;

  while (ros::ok()){
    time = ros::Time::now();
    br.sendTransform(tf::StampedTransform(transformUS1, time, "base_link", "ultrasound1"));
    br.sendTransform(tf::StampedTransform(transformUS2, time, "base_link", "ultrasound2"));
    br.sendTransform(tf::StampedTransform(transformUS3, time, "base_link", "ultrasound3"));
    br.sendTransform(tf::StampedTransform(transformUS4, time, "base_link", "ultrasound4"));
    loop_rate.sleep();
    ros::spinOnce();
  }
  return 0;
}
