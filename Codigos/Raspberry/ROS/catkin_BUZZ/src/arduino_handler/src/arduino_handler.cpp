#include "ros/ros.h"
#include "arduino_msgs/StampedInt64.h"
#include "sensor_msgs/Range.h"

#define US01 555
#define US02 556
#define US03 557
#define US04 558


// Valores - Ultrassom 1
long long int ultrasound1_value = -1;
ros::Time ultrasound1_time;

// Valores - Ultrassom 2
long long int ultrasound2_value = -1;
ros::Time ultrasound2_time;

// Valores - Ultrassom 3
long long int ultrasound3_value = -1;
ros::Time ultrasound3_time;

// Valores - Ultrassom 4
long long int ultrasound4_value = -1;
ros::Time ultrasound4_time;



void stampedInt64Callback(const arduino_msgs::StampedInt64::ConstPtr& msg)
{
 // ROS_INFO("Id: [%lld]",msg->id);
 // ROS_INFO("Data: [%lld]", msg->data);
  if(msg->id == US01){
    ultrasound1_value = msg->data;
    ultrasound1_time = ros::Time::now();

  }else if(msg->id == US02){
    ultrasound2_value = msg->data;
    ultrasound2_time = ros::Time::now();

  }else if(msg->id == US03){
    ultrasound3_value = msg->data;
    ultrasound3_time = ros::Time::now();

  }else if(msg->id == US04){
    ultrasound4_value = msg->data;
    ultrasound4_time = ros::Time::now();

  }else if(msg->id == 999){
    ROS_INFO("Id: [%lld]",msg->id);
    ROS_INFO("Data: [%lld]", msg->data);
  }


}

sensor_msgs::Range createRangeMsg1(){
  sensor_msgs::Range range_msg;
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  "/ultrasound1";
  range_msg.field_of_view = 0.2618;
  range_msg.min_range = 0.0;
  range_msg.max_range = 0.51;
  range_msg.range = ultrasound1_value/(float)100;
  range_msg.header.stamp = ultrasound1_time;
  return range_msg;
}

sensor_msgs::Range createRangeMsg2(){
  sensor_msgs::Range range_msg;
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  "/ultrasound2";
  range_msg.field_of_view = 0.2618;
  range_msg.min_range = 0.0;
  range_msg.max_range = 0.51;
  range_msg.range = ultrasound2_value/(float)100;
  range_msg.header.stamp = ultrasound2_time;
  return range_msg;
}

sensor_msgs::Range createRangeMsg3(){
  sensor_msgs::Range range_msg;
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  "/ultrasound3";
  range_msg.field_of_view = 0.2618;
  range_msg.min_range = 0.0;
  range_msg.max_range = 0.51;
  range_msg.range = ultrasound3_value/(float)100;
  range_msg.header.stamp = ultrasound3_time;
  return range_msg;
}

sensor_msgs::Range createRangeMsg4(){
  sensor_msgs::Range range_msg;
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  "/ultrasound4";
  range_msg.field_of_view = 0.2618;
  range_msg.min_range = 0.0;
  range_msg.max_range = 0.51;
  range_msg.range = ultrasound4_value/(float)100;
  range_msg.header.stamp = ultrasound4_time;
  return range_msg;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "arduino_handler");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("arduino_int64", 1000, stampedInt64Callback);
  ros::Publisher ultrasound1_pub = n.advertise<sensor_msgs::Range>("ultrasound1", 1000);
  ros::Publisher ultrasound2_pub = n.advertise<sensor_msgs::Range>("ultrasound2",1000);
  ros::Publisher ultrasound3_pub = n.advertise<sensor_msgs::Range>("ultrasound3",1000);
  ros::Publisher ultrasound4_pub = n.advertise<sensor_msgs::Range>("ultrasound4",1000);


  ros::Rate loop_rate(10);

  while (ros::ok()){
    sensor_msgs::Range range_msg1 = createRangeMsg1();
    sensor_msgs::Range range_msg2 = createRangeMsg2();
    sensor_msgs::Range range_msg3 = createRangeMsg3();
    sensor_msgs::Range range_msg4 = createRangeMsg4();


    ultrasound1_pub.publish(range_msg1);
    ultrasound2_pub.publish(range_msg2);
    ultrasound3_pub.publish(range_msg3);
    ultrasound4_pub.publish(range_msg4);


    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;
}
