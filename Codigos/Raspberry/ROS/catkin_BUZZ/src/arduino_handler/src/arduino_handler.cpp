#include "ros/ros.h"
#include "arduino_msgs/StampedInt64.h"
#include "arduino_msgs/StampedFloat64.h"
#include "raspberry_msgs/StampedFloat32.h"
#include "raspberry_msgs/GPS.h"
#include "sensor_msgs/Range.h"
#include "geometry_msgs/Point32.h"
#include "std_msgs/Bool.h"
#include <string>
#include <sstream>

#define VEL_REF_DIR 10
#define VEL_REF_ESQ 11

#define SENSOR_TOQUE 300
#define BOTAO_VERDE 301
#define BOTAO_PRETO 302

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

#define GPS_LAT 666
#define GPS_LON 667
#define GPS_ALT 668
#define GPS_VALID 669
#define GPS_HDOP 670
#define GPS_SPEED 671
#define GPS_COURSE 672
#define GPS_UPDATED 673

#define VEL_ATUAL_DIR 798
#define VEL_ATUAL_ESQ 799

#define NUM_US 11

#define MAX_DIST 200

/*
Quicksort
*/

#define MEDIAN_SIZE 5
#define MEDIAN_VALUE 2

ros::Publisher velocity_pub;

template<typename ItemType>
unsigned Partition(ItemType* array, unsigned f, unsigned l, ItemType pivot)
{
    unsigned i = f-1, j = l+1;
    while(true)
    {
        while(pivot < array[--j]);
        while(array[++i] < pivot);
        if(i<j)
        {
            ItemType tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
        else
            return j;
    }
}

template<typename ItemType>
void QuickSortImpl(ItemType* array, unsigned f, unsigned l)
{
    while(f < l)
    {
        unsigned m = Partition(array, f, l, array[f]);
        QuickSortImpl(array, f, m);
        f = m+1;
    }
}

template<typename ItemType>
void QuickSort(ItemType* array, unsigned size)
{
    QuickSortImpl(array, 0, size-1);
}

/*
Quicksort
*/


// Valores - Ultrassom
struct Ultrasound{
  float value;
  float values[MEDIAN_SIZE];
  long long int times_read;
  ros::Time time;
};

struct GPSData{

	bool valid;
	double lat;
	double lng;
	double alt;
	double speed;
	double course;
	float hdop;
	bool updated;
	

};

Ultrasound ultrasound[NUM_US];
sensor_msgs::Range range_msgs[NUM_US];
GPSData gpsData;

static bool sensor_toque = false;
static bool botao_verde = false;
static bool botao_preto = false;

static float velocidadeAtualEsq = 0.0;
static float velocidadeAtualDir = 0.0;

double oldLat = 0.0;
double oldLng = 0.0;

raspberry_msgs::StampedFloat32 velocidadeArduino;

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
    long long int value = msg->data;
    if(value == 0){  
      value = MAX_DIST;
    }
    float k = 0.8;
    float fValue = ((float)value/100.0);
    long long int iterator = ultrasound[usPos].times_read;
    ultrasound[usPos].values[iterator % MEDIAN_SIZE] = fValue;
    float values[MEDIAN_SIZE];
    for(unsigned i = 0; i < MEDIAN_SIZE; ++i) {
      values[i] = ultrasound[usPos].values[i];
    }
    QuickSort(values,MEDIAN_SIZE);
    //ultrasound[usPos].value = values[MEDIAN_VALUE];
    fValue = values[MEDIAN_VALUE];
    ultrasound[usPos].value = fValue*k + ultrasound[usPos].value*(1-k);
    ultrasound[usPos].time = ros::Time::now();
    ultrasound[usPos].times_read++;
  }else if(msg->id == SENSOR_TOQUE){
    sensor_toque = msg->data;
  }else if(msg->id == BOTAO_PRETO){
    botao_preto = msg->data;
  }else if(msg->id == BOTAO_VERDE){
    botao_verde = msg->data;
  }else if(msg->id == GPS_VALID){
 	gpsData.valid = msg->data;	  	
  }
}

void stampedFloat64Callback(const arduino_msgs::StampedFloat64::ConstPtr& msg){
  if(msg->id == VEL_ATUAL_DIR){
    velocidadeAtualDir = msg->data;
  }else if(msg->id == VEL_ATUAL_ESQ){
    velocidadeAtualEsq = msg->data;
  }else if(msg->id == GPS_LAT){
 	gpsData.lat = msg->data;
	if(gpsData.lat != oldLat){
		gpsData.updated = true;
		oldLat = gpsData.lat;
	}else{
		gpsData.updated = false;
	}	  	
  }else if(msg->id == GPS_LON){
 	gpsData.lng = msg->data;	
	if(gpsData.lng != oldLng){
                gpsData.updated = true;
                oldLng = gpsData.lng;
        }else{
                gpsData.updated = false;
        }
  	
  }else if(msg->id == GPS_HDOP){
    gpsData.hdop = msg->data;
  }else if(msg->id == GPS_SPEED){
    gpsData.speed = msg->data;      
  }else if(msg->id == GPS_COURSE){
    gpsData.course= msg->data;      
  }


}

void arduinoVelocityCallback(const raspberry_msgs::StampedFloat32::ConstPtr& msg){
  velocidadeArduino.id = msg->id;
  velocidadeArduino.data = msg->data;
  velocity_pub.publish(velocidadeArduino);
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

  ros::Subscriber subInt = n.subscribe("arduino_int64", 1000, stampedInt64Callback);
  ros::Subscriber subFloat = n.subscribe("arduino_float64", 1000, stampedFloat64Callback);  
  ros::Subscriber arduino_velocity = n.subscribe("arduino_velocity", 1000, arduinoVelocityCallback);

  ros::Publisher ultrasound_pub[NUM_US];

  ros::Publisher sensor_toque_pub = n.advertise<std_msgs::Bool>("sensor_toque",1000);
  ros::Publisher botao_verde_pub = n.advertise<std_msgs::Bool>("botao_verde",1000);
  ros::Publisher botao_preto_pub = n.advertise<std_msgs::Bool>("botao_preto",1000);

  ros::Publisher velocidade_atual_pub = n.advertise<geometry_msgs::Point32>("velocidade_atual",1000);
  ros::Publisher gps_pub = n.advertise<raspberry_msgs::GPS>("gpsInfo",1000);

  velocity_pub = n.advertise<raspberry_msgs::StampedFloat32>("raspberry_float32", 1000,true);

  for(int i=0;i<NUM_US;i++){
    std::ostringstream s;
    s << i+1;
    std::string name = std::string("ultrasound")+s.str();
    ultrasound_pub[i] = n.advertise<sensor_msgs::Range>(name, 1000);
  }

  startRangeMsgs();
  ros::Rate loop_rate(10);

  std_msgs::Bool sensor_toque_msg;
  std_msgs::Bool botao_preto_msg;
  std_msgs::Bool botao_verde_msg;
  geometry_msgs::Point32 velocidade_atualMsg;
  raspberry_msgs::GPS gps_msg;

  while (ros::ok()){
    processRangeMsgs();
    sensor_toque_msg.data = sensor_toque;
    botao_verde_msg.data = botao_verde;
    botao_preto_msg.data = botao_preto;
    velocidade_atualMsg.x = velocidadeAtualDir;
    velocidade_atualMsg.y = velocidadeAtualEsq;
    gps_msg.valid = gpsData.valid;
    gps_msg.lat = gpsData.lat;
    gps_msg.lng = gpsData.lng;
    gps_msg.hdop = gpsData.hdop;
    gps_msg.speed = gpsData.speed;
    gps_msg.course = gpsData.course;
    gps_msg.updated = gpsData.updated;

    for(int i=0;i<NUM_US;i++){
      ultrasound_pub[i].publish(range_msgs[i]);
    }
    sensor_toque_pub.publish(sensor_toque_msg);
    botao_verde_pub.publish(botao_verde_msg);
    botao_preto_pub.publish(botao_preto_msg);
    velocidade_atual_pub.publish(velocidade_atualMsg);
    gps_pub.publish(gps_msg);

    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;
}
