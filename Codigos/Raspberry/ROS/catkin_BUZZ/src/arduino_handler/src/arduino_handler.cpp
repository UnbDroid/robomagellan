#include "ros/ros.h"
#include "arduino_msgs/StampedInt64.h"
#include "raspberry_msgs/StampedFloat32.h"
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

/*
Quicksort
*/

#define MEDIAN_SIZE 5
#define MEDIAN_VALUE 2

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

Ultrasound ultrasound[NUM_US];
sensor_msgs::Range range_msgs[NUM_US];

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
  }


}

void arduinoVelocityCallback(const raspberry_msgs::StampedFloat32::ConstPtr& msg){
  velocidadeArduino.id = msg->id;
  velocidadeArduino.data = msg->data;
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
  ros::Subscriber arduino_velocity = n.subscribe("arduino_velocity", 1000, arduinoVelocityCallback);

  ros::Publisher ultrasound_pub[NUM_US];

  ros::Publisher velocity_pub = n.advertise<raspberry_msgs::StampedFloat32>("raspberry_float32", 1000);

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

    velocity_pub.publish(velocidadeArduino);

    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;
}
