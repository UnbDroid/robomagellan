#include <ros.h>
#include <ros/time.h>
#include <raspberry_msgs/StampedInt64.h>
#include <raspberry_msgs/StampedFloat32.h>
#include <raspberry_msgs/StampedFloat64.h>

#define US01 555
#define US02 556
#define US03 557
#define US04 558

#define LED A15

#include <Ultrasonic.h>

Ultrasonic ultrasonic1(22,23); // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic2(52,53); // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic3(24,25); // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic4(50,51); // (Trig PIN,Echo PIN)

ros::NodeHandle  nh;

void sendInt64(int id, int data);
void initializeRosCom();


void messageInt64Cb( const raspberry_msgs::StampedInt64& r_int64_msg){
  if(r_int64_msg.id == 64){
    sendInt64(999,r_int64_msg.data+32);
  }else if(r_int64_msg.id == 75){
    analogWrite(LED, r_int64_msg.data);
  }
}

void messageFloat32Cb( const raspberry_msgs::StampedFloat32& r_float32_msg){
  if(r_float32_msg.id == 64){
    sendInt64(999,r_float32_msg.data+32);
  }
}

void messageFloat64Cb( const raspberry_msgs::StampedFloat64& r_float64_msg){
  if(r_float64_msg.id == 64){
    sendInt64(999,r_float64_msg.data+32);
    pinMode(LED,OUTPUT);
  }
}

void setup(){
  initializeRosCom();
}

long range_time;

void loop(){
  if ( millis() >= range_time ){
    sendInt64(US01, ultrasonic1.Ranging(CM));
    sendInt64(US02, ultrasonic2.Ranging(CM));
    sendInt64(US03, ultrasonic3.Ranging(CM));
    sendInt64(US04, ultrasonic4.Ranging(CM));
    range_time =  millis() + 50;
  }
  nh.spinOnce();
}
