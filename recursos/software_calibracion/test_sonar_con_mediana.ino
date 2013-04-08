#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 76 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define NUM_OF_SHOTS 5


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(500);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  //unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
 
 
  int median = sonar.ping_median(NUM_OF_SHOTS);
  Serial.print("Ping: ");
  Serial.print((median / US_ROUNDTRIP_CM)-1); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}

