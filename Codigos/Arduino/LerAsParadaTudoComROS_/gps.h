#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include <SD.h>

#define CS 53

TinyGPSPlus gps;

double lat,lon,alt;
bool gps_valid;

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
  if (gps.location.isValid())
  {
    lat = gps.location.lat();
    lon = gps.location.lng();
    alt = gps.altitude.meters();
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
