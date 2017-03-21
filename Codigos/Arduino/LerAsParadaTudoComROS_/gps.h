#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>

TinyGPSPlus gps;

double lat,lon,alt;

void displayInfo()
{
  //Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    lat = gps.location.lat();
    lon = gps.location.lng();
    alt = gps.altitude.meters();
    Serial.print(lat,8);
    Serial.print(F("\t"));
    Serial.print(lon,8);
    Serial.print(F("\t"));
    Serial.print(alt,8);
    Serial.println();
  }
  else
  {
   // Serial.print(F("INVALID"));
    lat = 0;
    lon = 0;
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
