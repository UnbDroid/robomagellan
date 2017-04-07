/*

Biblioteca baseada na TinyGPS++ para arduino

*/

#include <stdint.h>

#ifndef __gps_h
#define __gps_h

#define _GPS_KMPH_PER_KNOT 1.852
#define _GPS_KM_PER_METER 0.001
#define _GPS_MAX_FIELD_SIZE 15

struct RawDegrees
{
   uint16_t deg;
   uint32_t billionths;
   bool negative;
public:
   RawDegrees() : deg(0), billionths(0), negative(false)
   {}
};

struct TinyGPSLocation
{
   friend class GPS;
public:
   bool isValid() const    { return valid; }
   bool isUpdated() const  { return updated; }
   const RawDegrees &rawLat()     { updated = false; return rawLatData; }
   const RawDegrees &rawLng()     { updated = false; return rawLngData; }
   double lat();
   double lng();

   TinyGPSLocation() : valid(false), updated(false)
   {}

private:
   bool valid, updated;
   RawDegrees rawLatData, rawLngData, rawNewLatData, rawNewLngData;
   void commit();
   void setLatitude(const char *term);
   void setLongitude(const char *term);
};


struct TinyGPSTime
{
   friend class GPS;
public:
   bool isValid() const       { return valid; }
   bool isUpdated() const     { return updated; }

   uint32_t value()           { updated = false; return time; }
   uint8_t hour();
   uint8_t minute();
   uint8_t second();
   uint8_t centisecond();
   uint32_t getTime(){return time;};

   TinyGPSTime() : valid(false), updated(false), time(0)
   {}

private:
   bool valid, updated;
   uint32_t time, newTime;
   void commit();
   void setTime(const char *term);
 
};

struct TinyGPSDecimal
{
   friend class GPS;
public:
   bool isValid() const    { return valid; }
   bool isUpdated() const  { return updated; }
   int32_t value()         { updated = false; return val; }

   TinyGPSDecimal() : valid(false), updated(false), val(0)
   {}

private:
   bool valid, updated;
   int32_t val, newval;
   void commit();
   void set(const char *term);
};

struct TinyGPSInteger
{
   friend class GPS;
public:
   bool isValid() const    { return valid; }
   bool isUpdated() const  { return updated; }
   uint32_t value()        { updated = false; return val; }

   TinyGPSInteger() : valid(false), updated(false), val(0)
   {}

private:
   bool valid, updated;
   uint32_t val, newval;
   void commit();
   void set(const char *term);
};

struct TinyGPSSpeed : TinyGPSDecimal
{
   double knots()    { return value() / 100.0; }
   double kmph()     { return _GPS_KMPH_PER_KNOT * value() / 100.0; }

};

struct TinyGPSCourse : public TinyGPSDecimal
{
   double deg()      { return value() / 100.0; }
};

struct TinyGPSAltitude : TinyGPSDecimal
{
   double meters()       { return value() / 100.0; }
   double kilometers()   { return _GPS_KM_PER_METER * value() / 100.0; }
   
};

struct TinyGPSDOP : TinyGPSDecimal
{
   double realValue()       { return value() / 100.0; }
   
};

class GPS;

class GPS
{
public:
  GPS();
  bool encode(char c); // process one character received from GPS
  GPS &operator << (char c) {encode(c); return *this;}

  TinyGPSLocation location;
  TinyGPSTime time;
  TinyGPSSpeed speed;
  TinyGPSCourse course;
  TinyGPSAltitude altitude;
  TinyGPSInteger satellites;
  TinyGPSDOP hdop;
  TinyGPSDOP vdop;
  TinyGPSDOP pdop;

  static int32_t parseDecimal(const char *term);
  static void parseDegrees(const char *term, RawDegrees &deg);

  uint32_t charsProcessed()   const { return encodedCharCount; }
  uint32_t sentencesWithFix() const { return sentencesWithFixCount; }
  uint32_t failedChecksum()   const { return failedChecksumCount; }
  uint32_t passedChecksum()   const { return passedChecksumCount; }

private:
  enum {GPS_SENTENCE_GPGGA, GPS_SENTENCE_GPRMC, GPS_SENTENCE_GPGSA, GPS_SENTENCE_OTHER};

  // parsing state variables
  uint8_t parity;
  bool isChecksumTerm;
  char term[_GPS_MAX_FIELD_SIZE];
  uint8_t curSentenceType;
  uint8_t curTermNumber;
  uint8_t curTermOffset;
  bool sentenceHasFix;


  // statistics
  uint32_t encodedCharCount;
  uint32_t sentencesWithFixCount;
  uint32_t failedChecksumCount;
  uint32_t passedChecksumCount;

  // internal utilities
  int fromHex(char a);
  bool endOfTermHandler();
};

#endif