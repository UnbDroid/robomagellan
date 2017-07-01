#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "raspberry_msgs/Mag.h"
#include "raspberry_msgs/ParamMag.h"
#include <time.h>
#include "rosbag/bag.h"
#include <rosbag/view.h>
#include <boost/foreach.hpp>


#define DEBUG

#define foreach BOOST_FOREACH

#define SCALE 0.15

 //bias e fator dse escala de cada eixo do sensor
#define BX -0.0618718
#define BY -0.0261594
#define BZ -0.571556
//#define SX 1.02559
//#define SY 0.987607 #define foreach BOOST_FOREACH
//#define SZ 0.97193

rosbag::Bag bag;
ros::Time tempo;

short read_word(int fd, int adr_h,int adr_l){

	char high = wiringPiI2CReadReg8 (fd,adr_h);
//	ROS_INFO("High %d",high);
	char st2h = wiringPiI2CReadReg8 (fd,0x09);
	char low = wiringPiI2CReadReg8 (fd,adr_l);
	char st2l = wiringPiI2CReadReg8 (fd,0x09);
//	ROS_INFO("Low %d",low);
	
	short val = 0;

	if(!(st2h&0x08) && !(st2l&0x08))
		val = ((high << 8) + low);
//	ROS_INFO("Val %d", val);
	return val;

}


int main(int argc, char **argv){

	float bx, by, bz, sx, sy, sz;

    int Register_BypassEn = 0x37;
	
	int Register_Control = 0x0A;
   	int Register_XL = 0x03;
   	int Register_XH = 0x04;
   	int Register_YL = 0x05;
   	int Register_YH = 0x06;
   	int Register_ZL = 0x07;
   	int Register_ZH = 0x08;
   	int Register_ST1 = 0x02;
   	int Register_ST2 = 0x09;

	short mag_x = 0;
	short mag_y = 0;
	short mag_z = 0;
	short mag_st2;

	//mpu adress
	int fd_mpu = wiringPiI2CSetup(0x68);
	
	// enable bypass mode (pra ler o mag)
	wiringPiI2CWriteReg8 (fd_mpu, Register_BypassEn,  0x02);  // 

	// mag adress
	int fd = wiringPiI2CSetup(0x0C);
	//std::cout << "fd: " << fd << std::endl;

	wiringPiI2CWriteReg8 (fd, Register_Control,  22);
	
	ros::init(argc, argv, "mag");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<raspberry_msgs::Mag>("magInfo", 1000);
	ros::Rate loop_rate(100);

// Leitura parametros
//------------------------------------------------------------------
/*rosbag::Bag bagParam;
        bagParam.open("/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/parametrosMag.bag", rosbag::bagmode::Read);

 	std::vector<std::string> topics;
    	topics.push_back(std::string("param_mag"));
   
    	rosbag::View view(bagParam, rosbag::TopicQuery(topics));

	foreach(rosbag::MessageInstance const m, view){
		raspberry_msgs::ParamMag::ConstPtr s = m.instantiate<raspberry_msgs::ParamMag>();
		if (s != NULL){
			bx = s->bx;
			by = s->by;
			bz = s->bz;
			sx = s->sx;
			sy = s->sy;
			sz = s->sz;
		
		}
	}

	bagParam.close(); */ 
//-------------------------------------------------------------------

	bag.open("/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/src/imu/scripts/mag5.bag", rosbag::bagmode::Write);
	
	raspberry_msgs::Mag msg;

	int count = 0;
	short st1;
	
	while (ros::ok()){
	
	//do{
	
		//st1 =  wiringPiI2CReadReg8 (fd,Register_ST1);
	//}while(!(st1&0x01));

		//leituras raw
		
		//wiringPiI2CWriteReg8 (fd, Register_Control,  0x01);
		
		mag_x = read_word(fd,Register_XH,Register_XL);
		mag_y = read_word(fd,Register_YH,Register_YL);
		mag_z = read_word(fd,Register_ZH,Register_ZL);


		msg.m_x = (mag_y*SCALE) - 12;
       		msg.m_y = (mag_x*SCALE) - 4;
       		msg.m_z = -(mag_z*SCALE) -43;
		tempo = ros::Time::now();
		msg.tempo = tempo.toNSec() * 1e-6;
		
		#ifdef DEBUG
		ROS_INFO("x: %f", msg.m_x);
		ROS_INFO("y: %f", msg.m_y);
		ROS_INFO("z: %f", msg.m_z);

		bag.write("mag_data",ros::Time::now(),msg);
		#endif

		chatter_pub.publish(msg);
	    
		ros::spinOnce();
	
	    	loop_rate.sleep();
	    	++count;
	}

	bag.close();	
	
 return 0;
}
