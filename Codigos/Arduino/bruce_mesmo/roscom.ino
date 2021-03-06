#include <arduino_msgs/StampedUint8.h>
#include <arduino_msgs/StampedUint32.h>
#include <arduino_msgs/StampedUint64.h>
#include <arduino_msgs/StampedInt8.h>
#include <arduino_msgs/StampedInt32.h>
#include <arduino_msgs/StampedInt64.h>
#include <arduino_msgs/StampedBool.h>
#include <arduino_msgs/StampedChar.h>
#include <arduino_msgs/StampedFloat32.h>
#include <arduino_msgs/StampedFloat64.h>
#include <arduino_msgs/StampedString.h>

#include <raspberry_msgs/StampedUint8.h>
#include <raspberry_msgs/StampedUint32.h>
#include <raspberry_msgs/StampedUint64.h>
#include <raspberry_msgs/StampedInt8.h>
#include <raspberry_msgs/StampedInt32.h>
#include <raspberry_msgs/StampedInt64.h>
#include <raspberry_msgs/StampedBool.h>
#include <raspberry_msgs/StampedChar.h>
#include <raspberry_msgs/StampedFloat32.h>
#include <raspberry_msgs/StampedFloat64.h>
#include <raspberry_msgs/StampedString.h>


//arduino_msgs::StampedUint8 uint8_msg;
//arduino_msgs::StampedUint32 uint32_msg;
//arduino_msgs::StampedUint64 uint64_msg;

//arduino_msgs::StampedInt8 int8_msg;
//arduino_msgs::StampedInt32 int32_msg;
arduino_msgs::StampedInt64 int64_msg;

arduino_msgs::StampedFloat32 float32_msg;
arduino_msgs::StampedFloat64 float64_msg;

//arduino_msgs::StampedString string_msg;
//arduino_msgs::StampedBool bool_msg;
//arduino_msgs::StampedChar char_msg;

//ros::Publisher int8_p("arduino_int8",&int8_msg);
//ros::Publisher int32_p("arduino_int32",&int32_msg);
ros::Publisher int64_p("arduino_int64",&int64_msg);

//ros::Publisher uint8_p("arduino_uint8",&uint8_msg);
//ros::Publisher uint32_p("arduino_uint32",&uint32_msg);
//ros::Publisher uint64_p("arduino_uint64",&uint64_msg);

ros::Publisher float32_p("arduino_float32",&float32_msg);
ros::Publisher float64_p("arduino_float64",&float64_msg);

//ros::Publisher string_p("arduino_string",&string_msg);

//ros::Publisher bool_p("arduino_bool",&bool_msg);

//ros::Publisher char_p("arduino_char",&char_msg);


ros::Subscriber<raspberry_msgs::StampedInt64> subInt64("raspberry_int64", &messageInt64Cb );
ros::Subscriber<raspberry_msgs::StampedFloat32> subFloat32("raspberry_float32", &messageFloat32Cb );
ros::Subscriber<raspberry_msgs::StampedFloat64> subFloat64("raspberry_float64", &messageFloat64Cb );

void initializeRosCom(){
  nh.initNode();

  //nh.advertise(uint8_p);
  //nh.advertise(uint32_p);
  //nh.advertise(uint64_p);

  //nh.advertise(int8_p);
  //nh.advertise(int32_p);
  nh.advertise(int64_p);

  //nh.advertise(char_p);
  //nh.advertise(bool_p);
  //nh.advertise(string_p);

  nh.advertise(float32_p);
  nh.advertise(float64_p);
  
  nh.subscribe(subInt64);
  nh.subscribe(subFloat32);
  nh.subscribe(subFloat64);
}


void sendInt64(int id, int data){
   int64_msg.id = id;
   int64_msg.data = data;
   int64_p.publish(&int64_msg);
}

void sendFloat32(int id, float data){
   float32_msg.id = id;
   float32_msg.data = data;
   float32_p.publish(&float32_msg);
}

void sendFloat64(int id, double data){
   float64_msg.id = id;
   float64_msg.data = data;
   float64_p.publish(&float64_msg);
}

