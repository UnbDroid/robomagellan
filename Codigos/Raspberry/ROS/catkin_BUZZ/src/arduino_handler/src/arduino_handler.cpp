#include "ros/ros.h"
#include "arduino_msgs/StampedInt64.h"
#include "sensor_msgs/Range.h"
#include <string>
#include <sstream>

#define SENSOR_TOQUE 300

#define US01 555
#define US02 556
#define US03 557
#define US04 558
#define US05 559
#define US06 560
#define US07 561
#define US08 562
#define US09 563
#define US10 564
#define US11 565

#define NUM_US 11

#define GPS_LAT 666
#define GPS_LON 667
#define GPS_ALT 668
#define GPS_VALID 669
#define GPS_UPDATED 670

#define VEL_ATUAL_DIR 798
#define VEL_ATUAL_ESQ 799

#define MAX_DIST 200

// Valores - Ultrassom
struct Ultrasound{
  float value;
  float times_read;
  ros::Time time;
};

Ultrasound ultrasound[NUM_US];
sensor_msgs::Range range_msgs[NUM_US];


int verifyIfUS(long int id){
  int USIds[NUM_US] = {US01,US02,US03,US04,US05,US06,US07,US08,US09,US10,US11};
  for(int i=0;i<NUM_US;i++){
    if(USIds[i]==id){
      return i;
    }
  }
  return -1;
}

void stampedInt64Callback(const arduino_msgs::StampedInt64::ConstPtr& msg){
  int usPos = verifyIfUS(msg->id);
  if(usPos > -1){
    ultrasound[usPos].times_read += 1;
    long long int value = msg->data;
//    ultrasound[usPos].value = msg->data;
//    if(ultrasound[usPos].value == 0){
    if(value == 0){  
      value = MAX_DIST;
    }
    float k = 1;
    ultrasound[usPos].value = ((float)value/100.0)*k + ultrasound[usPos].value*(1-k);
    ultrasound[usPos].time = ros::Time::now();

  }


}

void processRangeMsgs(){
  for(int i=0;i<NUM_US;i++){
    range_msgs[i].range = ultrasound[i].value;
    range_msgs[i].header.stamp = ultrasound[i].time;
  }
}

void startRangeMsgs(){
  std::string USFrame[NUM_US] = {"/ultrasound1","/ultrasound2","/ultrasound3","/ultrasound4","/ultrasound5","/ultrasound6","/ultrasound7","/ultrasound8","/ultrasound9","/ultrasound10","/ultrasound11"};
  for(int i=0;i<NUM_US;i++){
    range_msgs[i].radiation_type = sensor_msgs::Range::ULTRASOUND;
    range_msgs[i].header.frame_id = USFrame[i] ;
    range_msgs[i].field_of_view = 0.2618;
    range_msgs[i].min_range = 0.0;
    range_msgs[i].max_range = 2;
    range_msgs[i].range = -1;
    range_msgs[i].header.stamp =  ros::Time::now();    
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "arduino_handler");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("arduino_int64", 1000, stampedInt64Callback);
  ros::Publisher ultrasound_pub[NUM_US];
  for(int i=0;i<NUM_US;i++){
    std::ostringstream s;
    s << i+1;
    std::string name = std::string("ultrasound")+s.str();
    ultrasound_pub[i] = n.advertise<sensor_msgs::Range>(name, 1000);
  }

  startRangeMsgs();
  ros::Rate loop_rate(10);

  while (ros::ok()){
    processRangeMsgs();

    for(int i=0;i<NUM_US;i++){
      ultrasound_pub[i].publish(range_msgs[i]);
    }

    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;
}
