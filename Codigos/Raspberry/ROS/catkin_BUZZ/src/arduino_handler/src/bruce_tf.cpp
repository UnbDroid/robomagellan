#include <ros/ros.h>
#include <tf/transform_broadcaster.h>



int main(int argc, char** argv){
  ros::init(argc, argv, "bruce_tf_broadcaster");

  ros::Time time;


  tf::TransformBroadcaster br;

  tf::Transform transformUS1(tf::Quaternion(0,0,-0.707,0.707),tf::Vector3(0,-0.19,0.2));

  tf::Transform transformUS2(tf::Quaternion(0,0,-0.588,0.809),tf::Vector3(0.06,-0.16,0.2));

  tf::Transform transformUS3(tf::Quaternion(0,0,- 0.454,0.891),tf::Vector3(0.12,-0.14,0.2));

  tf::Transform transformUS4(tf::Quaternion(0,0,-0.309, 0.951),tf::Vector3(0.15,-0.11,0.2));

  tf::Transform transformUS5(tf::Quaternion(0,0,-0.156,0.988),tf::Vector3(0.16,-0.06,0.2));

  tf::Transform transformUS6(tf::Quaternion(0,0,0,1),tf::Vector3(0.17,0,0.2));

  tf::Transform transformUS7(tf::Quaternion(0,0, 0.156, 0.988),tf::Vector3(0.16,0.06,0.2));

  tf::Transform transformUS8(tf::Quaternion(0,0,0.309, 0.951),tf::Vector3(0.15,0.11,0.2));

  tf::Transform transformUS9(tf::Quaternion(0,0, 0.454,0.891),tf::Vector3(0.12,0.14,0.2));

  tf::Transform transformUS10(tf::Quaternion(0,0,0.588,0.809),tf::Vector3(0.06,0.16,0.2));

  tf::Transform transformUS11(tf::Quaternion(0,0,0.707,0.707),tf::Vector3(0,0.19,0.2));

  ros::Rate loop_rate(10);

  ros::NodeHandle node;

  while (ros::ok()){
    time = ros::Time::now();
    br.sendTransform(tf::StampedTransform(transformUS1, time, "base_link", "ultrasound1"));
    br.sendTransform(tf::StampedTransform(transformUS2, time, "base_link", "ultrasound2"));
    br.sendTransform(tf::StampedTransform(transformUS3, time, "base_link", "ultrasound3"));
    br.sendTransform(tf::StampedTransform(transformUS4, time, "base_link", "ultrasound4"));
    br.sendTransform(tf::StampedTransform(transformUS5, time, "base_link", "ultrasound5"));
    br.sendTransform(tf::StampedTransform(transformUS6, time, "base_link", "ultrasound6"));
    br.sendTransform(tf::StampedTransform(transformUS7, time, "base_link", "ultrasound7"));
    br.sendTransform(tf::StampedTransform(transformUS8, time, "base_link", "ultrasound8"));
    br.sendTransform(tf::StampedTransform(transformUS9, time, "base_link", "ultrasound9"));
    br.sendTransform(tf::StampedTransform(transformUS10, time, "base_link", "ultrasound10"));
    br.sendTransform(tf::StampedTransform(transformUS11, time, "base_link", "ultrasound11"));        
    loop_rate.sleep();
    ros::spinOnce();
  }
  return 0;
}
