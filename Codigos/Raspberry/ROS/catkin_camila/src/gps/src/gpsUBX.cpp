#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "ros/ros.h"
#include "rosbag/bag.h"
#include "raspberry_msgs/GPS.h"
#include <wiringSerial.h>

const unsigned char UBX_HEADER[]         = { 0xB5, 0x62 };
const unsigned char NAV_POSECEF_HEADER[] = { 0x01, 0x01 };
const unsigned char NAV_STATUS_HEADER[]  = { 0x01, 0x03 };
const unsigned char NAV_VELNED_HEADER[]  = { 0x01, 0x12 };
const unsigned char NAV_POSLLH_HEADER[] = { 0x01, 0x02 };

enum _ubxMsgType {
  MT_NONE,
  MT_NAV_POSECEF,
  MT_NAV_STATUS,
  MT_NAV_VELNED,
  MT_NAV_POSLLH
};

struct NAV_POSECEF {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW; // GPS milisecond time of week // ms
  long ecefX; // cm
  long ecefY;
  long ecefZ;
  unsigned long pAcc; // position accuracy estimate // cm

};

struct NAV_STATUS {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;
  unsigned char gpsFix; 
  char flags; // gpsFixOk (bit 0)
  char fixStat;
  char flags2;
  unsigned long ttff; // time to first fix (ms time tag)
  unsigned long msss; // miliseconds since startup/reset 
};

struct NAV_VELNED {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW; // ms
  long velN; // cm/s
  long velE;
  long velD;
  unsigned long speed; // 3D speed 
  unsigned long gSpeed; // 2D speed (over ground)
  long heading; // graus
  unsigned long sAcc; // Speed accuracy estimate // cm/s
  unsigned long cAcc; // Course/heading accuracy estimate // graus
};

struct NAV_POSLLH {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;
  long lon;
  long lat;
  long height;
  long hMSL;
  unsigned long hAcc;
  unsigned long vAcc;
};


void configUBX(int fd){

const char disableGGA[16] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x24 };// GxGGA off
const char disableGLL[16] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x2B };// GxGLL off
const char disableGSA[16] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x02,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x32 };// GxGSA off
const char disableGSV[16] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x39 };// GxGSV off
const char disableRMC[16] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x04,0x00,0x00,0x00,0x00,0x00,0x01,0x04,0x40 };// GxRMC off
const char disableVTG[16] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x05,0x00,0x00,0x00,0x00,0x00,0x01,0x05,0x47 };// GxVTG off

const char enableSTATUS[16] = {  0xB5,0x62,0x06,0x01,0x08,0x00,0x01,0x03,0x00,0x01,0x00,0x00,0x00,0x00,0x14,0xC5}; //NAV-STATUS on
const char enablePOSECEF[16] = {0xB5,0x62,0x06,0x01,0x08,0x00,0x01,0x12,0x00,0x01,0x00,0x00,0x00,0x00,0x23,0x2E  }; //NAV-POSECEF on
const char enableVELNED[16] = {  0xB5,0x62,0x06,0x01,0x08,0x00,0x01,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x12,0xB7}; //NAV-VELNED on
const char enablePOSLLH[16] = {  0xB5,0x62,0x06,0x01,0x08,0x00,0x01,0x02,0x00,0x01,0x00,0x00,0x00,0x00,0x13,0xBE}; //NAV-POSLLHon

const char rate5[16] = {0xB5,0x62,0x06,0x08,0x06,0x00,0xC8,0x00,0x01,0x00,0x01,0x00,0xDE,0x6A}; //Rate 5Hz 

  int i = 0;
  
  while(i < 16){
	 write(fd,&disableGGA[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "dis gga" << std::endl;

i = 0;
usleep(5000);

  while(i < 16){
	 write(fd,&disableGLL[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "dis gll" << std::endl;

i = 0;
usleep(5000); 
    
    while(i < 16){
	 write(fd,&disableGSA[i],1);
	 usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "dis gsa" << std::endl;

i = 0;
usleep(5000);

  while(i < 16){
	 write(fd,&disableGSV[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "dis gsv" << std::endl;

i = 0;
usleep(5000);

  while(i < 16){
	 write(fd,&disableRMC[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "dis rmc" << std::endl;

i = 0;
usleep(5000);

  while(i < 16){
	 write(fd,&disableVTG[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "dis vtg" << std::endl;

i = 0;
usleep(5000);
	
	while(i < 16){
	 write(fd,&enableSTATUS[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "en status" << std::endl;

i = 0;
usleep(5000);  	
	
	while(i < 16){
	 write(fd,&enablePOSECEF[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "en posecef" << std::endl;

i = 0;
usleep(5000);
  	
	while(i < 16){
	 write(fd,&enableVELNED[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "en velned" << std::endl;

i = 0;
usleep(5000);
  	
while(i < 16){
	 write(fd,&enablePOSLLH[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "en posllh" << std::endl;

i = 0;
usleep(5000);
  	
	while(i < 16){
	 write(fd,&rate5[i],1);
	  usleep(5000); //micro segundo
 	 i++;
  }
std::cout << "en 5hz" << std::endl;

i = 0;
  	
	std::cout << "config" << std::endl;

}

union UBXMessage {
  NAV_POSECEF navPosEcef;
  NAV_STATUS navStatus;
  NAV_VELNED navVelNed;
  NAV_POSLLH navPosllh;
}ubxMessage;

//UBXMessage ubxMessage;

// The last two bytes of the message is a checksum value, used to confirm that the received payload is valid.
// The procedure used to calculate this is given as pseudo-code in the uBlox manual.
void calcChecksum(unsigned char* CK, int msgSize) {
	memset(CK, 0, 2);
	for (int i = 0; i < msgSize; i++) {
	    CK[0] += ((unsigned char*)(&ubxMessage))[i];
	    CK[1] += CK[0];
  }
}

// Compares the first two bytes of the ubxMessage struct with a specific message header.
// Returns true if the two bytes match.
bool compareMsgHeader(const unsigned char* msgHeader) {
	unsigned char* ptr = (unsigned char*)(&ubxMessage);
	return ptr[0] == msgHeader[0] && ptr[1] == msgHeader[1];
}

// Reads in bytes from the GPS module and checks to see if a valid message has been constructed.
// Returns the type of the message found if successful, or MT_NONE if no message was found.
// After a successful return the contents of the ubxMessage union will be valid, for the 
// message type that was found. Note that further calls to this function can invalidate the
// message content, so you must use the obtained values before calling this function again.
int processGPS(int fd) {

	int n, i = 0;
	unsigned char buf[64];
	static int fpos = 0;
	static unsigned char checksum[2];
  
	static char currentMsgType = MT_NONE;
	static int payloadSize = sizeof(UBXMessage);
   
	 n = read(fd, buf,1);
	 buf[n] = 0;  
	//std::cout<<payloadSize<<std::endl;
	 
	 while( buf[0] != 10 ){
	 //std::cout <<buf[0]<< std::endl;  
	    
    if ( fpos < 2 ) {
		// For the first two bytes we are simply looking for a match with the UBX header bytes (0xB5,0x62)
	    if ( buf[0] == UBX_HEADER[fpos] ){
  			//std::cout<<"ubx"<<std::endl;
			fpos++;
		}
        else
        	fpos = 0; // Reset to beginning state.
    }
    else {
    	 // If we come here then fpos >= 2, which means we have found a match with the UBX_HEADER
        // and we are now reading in the bytes that make up the payload.
      
        // Place the incoming byte into the ubxMessage struct. The position is fpos-2 because
        // the struct does not include the initial two-byte header (UBX_HEADER).
        if ( (fpos-2) < payloadSize )
			((unsigned char*)(&ubxMessage))[fpos-2] = buf[0];

        fpos++;
      
		if ( fpos == 4 ) {
       	// We have just received the second byte of the message type header, 
        // so now we can check to see what kind of message it is.
			if ( compareMsgHeader(NAV_POSECEF_HEADER) ) {
          		currentMsgType = MT_NAV_POSECEF;
          		payloadSize = sizeof(NAV_POSECEF);
          		std::cout << "ecef" << std::endl;
        	}
        else if ( compareMsgHeader(NAV_STATUS_HEADER) ) {
        	currentMsgType = MT_NAV_STATUS;
        	payloadSize = sizeof(NAV_STATUS);
        	std::cout << "status" << std::endl;
        }
        else if ( compareMsgHeader(NAV_VELNED_HEADER) ) {
        	currentMsgType = MT_NAV_VELNED;
        	payloadSize = sizeof(NAV_VELNED);
        	std::cout << "velned" << std::endl;
        }
        else if ( compareMsgHeader(NAV_POSLLH_HEADER) ) {
        	currentMsgType = MT_NAV_POSLLH;
            payloadSize = sizeof(NAV_POSLLH);
            std::cout << "psllh" << std::endl;
        }
        else {
        	// unknown message type, bail
			fpos = 0;
			//std::cout << "nop" << std::endl;
			continue;
        }
      }

      if ( fpos == (payloadSize+2) ) {
		// All payload bytes have now been received, so we can calculate the 
        // expected checksum value to compare with the next two incoming bytes.
        calcChecksum(checksum, payloadSize);
      }
      else if ( fpos == (payloadSize+3) ) {
        // First byte after the payload, ie. first byte of the checksum.
        // Does it match the first byte of the checksum we calculated?
        //std::cout<< "cs 1" << std::endl;
        if ( buf[0] != checksum[0] ) {
          // Checksum doesn't match, reset to beginning state and try again.
          fpos = 0;
	 std::cout<< "cs 1 fail" << std::endl;
	  
        }
      }
      else if ( fpos == (payloadSize+4) ) {
        // Second byte after the payload, ie. second byte of the checksum.
        // Does it match the second byte of the checksum we calculated?
        fpos = 0; // We will reset the state regardless of whether the checksum matches.
       // std::cout<< "cs 2" << std::endl;
        if ( buf[0] == checksum[1] ) {
          // Checksum matches, we have a valid message.
          std::cout<< "cs 2 ok" << std::endl;
          return currentMsgType; 
        }
      }
      else if ( fpos > (payloadSize+4) ) {
        // We have now read more bytes than both the expected payload and checksum 
        // together, so something went wrong. Reset to beginning state and try again.
        fpos = 0;
      }
    }
	n = read(fd, buf, 1);
	buf[n] = 0;
	i++;
   }
  return MT_NONE;
}


int main(int argc, char **argv){

	int fd, i;
  	char buf[2];
  	struct termios toptions;

	 /* open serial port */
	 fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
	 printf("fd opened as %i\n", fd);
  
	 /* wait for the Arduino to reboot */
	 usleep(1000);
  
  	/*Setup da comunicacao serial*/
	 /* get current serial port settings */
	 tcgetattr(fd, &toptions);
	 /* set 115200baud both ways */
	 cfsetispeed(&toptions, B9600);
	 cfsetospeed(&toptions, B9600);
	 /* 8 bits, no parity, no stop bits */
	 toptions.c_cflag &= ~PARENB;
	 toptions.c_cflag &= ~CSTOPB;
	 toptions.c_cflag &= ~CSIZE;
	 toptions.c_cflag |= CS8;
	 /* Canonical mode */
	 toptions.c_lflag |= ICANON;
	 /* commit the serial port settings */
	 tcsetattr(fd, TCSANOW, &toptions);
	 /*Fim do setup da comunicacao serial*/

	configUBX(fd);

	usleep(1000);
	
	ros::init(argc, argv, "gpsUBX");
	ros::NodeHandle n;
	ros::Rate loop_rate(5);
	ros::Publisher pub = n.advertise<raspberry_msgs::GPS>("gpsInfo",1000);
	rosbag::Bag gpsUBX;
	
	gpsUBX.open("/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/src/imu/scripts/gpsUBX5.bag", rosbag::bagmode::Write);	
	
	ros::Time tIndividual;

	raspberry_msgs::GPS msg;

	//char buf[2];

	while(ros::ok()){

	//i = read(fd,buf,1);
	//buf[i] = 0;
	//ROS_INFO("%c",buf[0]);
	//std::cout << buf[0];
	
		
 int msgType = processGPS(fd);
// std::cout<< "type: " << msgType << std::endl;
  
  if ( msgType == MT_NAV_POSECEF ) {
    std::cout<<"iTOW:";      std::cout<<ubxMessage.navPosEcef.iTOW<<std::endl;
    std::cout<<" ECEFX:";   std::cout<<ubxMessage.navPosEcef.ecefX/100.0<<std::endl; 
    std::cout<<" ECEFY:";   std::cout<<ubxMessage.navPosEcef.ecefY/100.0<<std::endl; 
    std::cout<<" ECEFZ:"; std::cout<<ubxMessage.navPosEcef.ecefZ/100.0<<std::endl; 
    std::cout<<" pAcc: ";    std::cout<<ubxMessage.navPosEcef.pAcc/100.0<<std::endl;
    std::cout<<std::endl;
   
    msg.iTow = ubxMessage.navPosEcef.iTOW;
    msg.ecefX = ubxMessage.navPosEcef.ecefX/100.0;
    msg.ecefY = ubxMessage.navPosEcef.ecefY/100.0;
    msg.ecefZ = ubxMessage.navPosEcef.ecefZ/100.0;
    msg.pAcc = ubxMessage.navPosEcef.pAcc/100.0; 
    
    msg.newPos = true;
    
  }
  else if ( msgType == MT_NAV_STATUS ) {
    
   short fixOk = (ubxMessage.navStatus.flags&0x01); 
    
    std::cout<<"gpsFix:";    std::cout<<(int)ubxMessage.navStatus.gpsFix<<std::endl;
    std::cout<<"gpsFixOk:";    std::cout<<fixOk<<std::endl;
    std::cout<<std::endl;
    //tIndividual = ros::Time::now();
    
    
    msg.gpsFix = (int)ubxMessage.navStatus.gpsFix;
    msg.gpsFixOk = fixOk;
    
    msg.newPos = false;
    
  }
  else if ( msgType == MT_NAV_VELNED ) {
    std::cout<<" VELN:"; std::cout<<ubxMessage.navVelNed.velN/100.0<<std::endl; 
   std::cout<<" VELE:"; std::cout<<ubxMessage.navVelNed.velE/100.0<<std::endl; 
    std::cout<<" VELD:"; std::cout<<ubxMessage.navVelNed.velD/100.0<<std::endl; 
    std::cout<<" Speed 3D:"; std::cout<<ubxMessage.navVelNed.speed/100.0<<std::endl; 
    std::cout<<" Speed 2D:"; std::cout<<ubxMessage.navVelNed.gSpeed/100.0<<std::endl;
    std::cout<<" Heading:"; std::cout<<ubxMessage.navVelNed.heading/100000.0<<std::endl;
    std::cout<<" cAcc: ";    std::cout<<ubxMessage.navVelNed.cAcc/100000.0<<std::endl;
    std::cout<<" sAcc: ";    std::cout<<ubxMessage.navVelNed.sAcc/100.0<<std::endl;
    std::cout<<std::endl;
    //tIndividual = ros::Time::now();
	
	
	msg.velN = ubxMessage.navVelNed.velN/100.0;
	msg.velE = ubxMessage.navVelNed.velE/100.0;
	msg.velD = ubxMessage.navVelNed.velD/100.0;
	msg.speed3D = ubxMessage.navVelNed.speed/100.0;
	msg.speed2D = ubxMessage.navVelNed.gSpeed/100.0;
	msg.heading = ubxMessage.navVelNed.heading/100000.0;
	msg.cAcc = ubxMessage.navVelNed.cAcc/100000.0;
	msg.sAcc = 	ubxMessage.navVelNed.sAcc/100.0;
	
	msg.newPos = false;
	 
  }

  else   if ( msgType == MT_NAV_POSLLH ) {
  std::cout.precision(9);
   std::cout<<"iTOW:";      std::cout<<ubxMessage.navPosllh.iTOW<<std::endl;
   std::cout<<" lat/lon: "; std::cout<<std::fixed<<ubxMessage.navPosllh.lat/10000000.0;  std::cout<< "   "; 				std::cout<<std::fixed<<ubxMessage.navPosllh.lon/10000000.0<<std::endl;
    std::cout<<" hAcc: ";    std::cout<<ubxMessage.navPosllh.hAcc/1000.0<<std::endl;
    std::cout<<std::endl;
    //ROS_INFO("");
    
    
    msg.lat = ubxMessage.navPosllh.lat/10000000.0; 
    msg.lng = ubxMessage.navPosllh.lon/10000000.0; 
    msg.hAcc = ubxMessage.navPosllh.hAcc/1000.0;
    msg.height = ubxMessage.navPosllh.height/1000.0;
    msg.vAcc = ubxMessage.navPosllh.vAcc/1000.0;
    
    msg.newPos = true;
  }
  else{
  	msg.newPos = false;  
  }
  
  if(msg.newPos ){
  	 tIndividual = ros::Time::now();
   	msg.tempo = tIndividual.toNSec() * 1e-6;
	gpsUBX.write("gps_data",ros::Time::now(),msg);
	pub.publish(msg);
	//std::cout << "oi";
  
  }

	
	ros::spinOnce();
	loop_rate.sleep();
	
	}

	gpsUBX.close();
	return 0;
}
