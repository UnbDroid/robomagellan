#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include <SD.h>

#define CS 53

TinyGPSPlus gps;

double lat,lon,alt,hdop,speed,course;
uint32_t age;
bool gps_valid,gps_updated;

const int chipSelect = CS;
int dataString = 0;
bool abriu = true;
char nomearquivo[] = "GPSdatalog.txt"; 

void start_SD(){
  
  pinMode(CS,OUTPUT);
  if(!SD.begin(chipSelect)){
    Serial.println("card failed");
    return;
    
    }
    Serial.println("card initialized");
    
  }

void displayInfo()
{

  /*File dataFile = SD.open("GPSdatalog.txt", FILE_WRITE);
  if(!dataFile){
     Serial.println("n tem arquivo");
     nomearquivo[13] = "datalog1.txt"; 
     dataFile = SD.open(nomearquivo, FILE_WRITE);
  }*/
  //Serial.print(F("Location: "));
  gps_valid = gps.location.isValid();
  //Serial.print("valid: ");Serial.println(gps_valid);
  if (gps_valid)
  {
    //gps_updated = gps.location.isUpdated();
    lat = gps.location.lat();
    lon = gps.location.lng();
    alt = gps.altitude.meters();
    speed = gps.speed.kmph();
    course = gps.course.deg();
    hdop = gps.hdop.value()/100.0;
    age = gps.location.age();
    if(age < 20){
      gps_updated = true;
    }else{
      gps_updated = false;
    }
   /* #ifndef ROS
      Serial.print("Lat: ");Serial.println(lat,8);
      Serial.print("Lng: ");Serial.println(lon,8);
      Serial.print("Speed: ");Serial.println(speed/3.6,8);
      Serial.print("Hdop: ");Serial.println(hdop,8);  
      Serial.print("valid: ");Serial.println(gps_valid);
      Serial.print("updated: ");Serial.println(gps_updated);
      Serial.print("Age: ");Serial.println(age);
      Serial.println("-----------------------------------------");
    #endif*/
    
    /*Serial.print(lat,8);
    Serial.print(F("\t"));
    Serial.print(lon,8);
    Serial.print(F("\t"));
    Serial.print(alt,8);
    Serial.println();*/

    /*if(dataFile){
      
      dataFile.print(millis());
      dataFile.print("\t");
      dataFile.print(lat,8);
      dataFile.print("\t");
      dataFile.print(lon,8);
      dataFile.print("\n");
      dataFile.close();
      
      
      }*/
    
    
  }
  else
  {
   //Serial.println(F("INVALID"));
    lat = 0;
    lon = 0;
    gps_updated = false;
    
    /*if(dataFile){
      
      dataFile.print("invalid");
      dataFile.close();
      
      }*/
  }
} 


void leituraTinyGps(){
  
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read())) {
      displayInfo();
    }
  
}

void start_GPS(){
  Serial2.begin(4800);
}

#endif
