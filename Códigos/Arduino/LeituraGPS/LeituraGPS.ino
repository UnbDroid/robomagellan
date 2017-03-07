#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define RXPIN 2
#define TXPIN 3

SoftwareSerial mySerial(RXPIN, TXPIN);
TinyGPSPlus gps;

double lat,lng,alt;

void displayInfo()
{
  //Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    lat = gps.location.lat();
    lng = gps.location.lng();
    alt = gps.altitude.meters();
    Serial.print(lat,8);
    Serial.print(F("\t"));
    Serial.print(lng,8);
    Serial.print(F("\t"));
    Serial.print(alt,8);
    Serial.println();
  }
  else
  {
    Serial.print(F("INVALID"));
    lat = 0;
    lng = 0;
  }
} 


void leituraTinyGps(){
  
  while (mySerial.available() > 0)
    if (gps.encode(mySerial.read())) {
      displayInfo();
    }
  
}

void leituraRaw(){
  
  byte a;
  if ( mySerial.available() > 0 ){
    a = mySerial.read(); // get the byte of data from the GPS
    Serial.write(a);
    
  }

}


void setup()
{
  Serial.begin(9600);
  mySerial.begin(4800);
}
void loop()
{
  
  leituraTinyGps();
  //leituraRaw();

}
