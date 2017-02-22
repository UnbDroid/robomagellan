// ---------------------------------------------------------------------------
// This example code was used to successfully communicate with 15 ultrasonic sensors. You can adjust
// the number of sensors in your project by changing SONAR_NUM and the number of NewPing objects in the
// "sonar" array. You also need to change the pins for each sensor for the NewPing objects. Each sensor
// is pinged at 33ms intervals. So, one cycle of all sensors takes 495ms (33 * 15 = 495ms). The results
// are sent to the "oneSensorCycle" function which currently just displays the distance data. Your project
// would normally process the sensor results in this function (for example, decide if a robot needs to
// turn and call the turn function). Keep in mind this example is event-driven. Your complete sketch needs
// to be written so there's no "delay" commands and the loop() cycles at faster than a 33ms rate. If other
// processes take longer than 33ms, you'll need to increase PING_INTERVAL so it doesn't get behind.
// ---------------------------------------------------------------------------
#include <NewPing.h>

#define TRIGGER_1 39 // 29
#define ECHO_1 41 // 27
#define TRIGGER_2 38
#define ECHO_2 40
#define TRIGGER_3 26
#define ECHO_3 28
#define TRIGGER_4 30
#define ECHO_4 32
#define TRIGGER_5 46
#define ECHO_5 48
#define TRIGGER_6 34
#define ECHO_6 36
#define TRIGGER_7 27 // 41
#define ECHO_7 29 // 39
#define TRIGGER_8 35 // 33
#define ECHO_8 37 // 31
#define TRIGGER_9 42
#define ECHO_9 44
#define TRIGGER_10 24 // 49
#define ECHO_10 22 // 47
#define TRIGGER_11 23 // 45
#define ECHO_11 25 // 43
#define TRIGGER_12 37
#define ECHO_12 35
#define TRIGGER_13 25
#define ECHO_13 23
#define TRIGGER_14 22
#define ECHO_14 24

#define SONAR_NUM     9 // Number of sensors.
#define MAX_DISTANCE 500 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 50 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  //NewPing(TRIGGER_1, ECHO_1, MAX_DISTANCE) // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(TRIGGER_2, ECHO_2, MAX_DISTANCE),
  NewPing(TRIGGER_3, ECHO_3, MAX_DISTANCE),
  NewPing(TRIGGER_4, ECHO_4, MAX_DISTANCE),
  NewPing(TRIGGER_5, ECHO_5, MAX_DISTANCE),
  NewPing(TRIGGER_6, ECHO_6, MAX_DISTANCE), // US1
  NewPing(TRIGGER_7, ECHO_7, MAX_DISTANCE),
  NewPing(TRIGGER_8, ECHO_8, MAX_DISTANCE),
  //NewPing(TRIGGER_9, ECHO_9, MAX_DISTANCE),
  NewPing(TRIGGER_10, ECHO_10, MAX_DISTANCE),
  NewPing(TRIGGER_11, ECHO_11, MAX_DISTANCE)
  //NewPing(TRIGGER_12, ECHO_12, MAX_DISTANCE),
  //NewPing(TRIGGER_13, ECHO_13, MAX_DISTANCE),
  //NewPing(50, 51, MAX_DISTANCE),
  //NewPing(52, 53, MAX_DISTANCE)
};

void oneSensorCycle();
void echoCheck();

void setup() {
  Serial.begin(115200);
  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
  // Other code that *DOESN'T* analyze ping results can go here.
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  Serial.println();
}
