#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "ros/ros.h"

int main(int argc, char **argv){

	int fd, n, i;
  	char buf[64] = "temp text";
  	struct termios toptions;

	 /* open serial port */
	 fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
	 printf("fd opened as %i\n", fd);
  
	 /* wait for the Arduino to reboot */
	 usleep(3500000);
  
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


	while(true){
	
		n = read(fd, buf,1);
		buf[n] = 0;
		std::cout << buf[0];
	
	}




}
