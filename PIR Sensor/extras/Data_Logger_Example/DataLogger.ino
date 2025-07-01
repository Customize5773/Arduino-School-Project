/* PIR Sensor with SD Card Logging
 * Requires:
 * - SD card module
 * - Arduino Uno
 * 
 * Wiring:
 * SD Module | Arduino
 *   VCC     -> 5V
 *   GND     -> GND
 *   MISO    -> D12
 *   MOSI    -> D11
 *   SCK     -> D13
 *   CS      -> D4
 */

#include <SPI.h>
#include <SD.h>

// Pins
const int PIR_PIN = 2;
const int LED_PIN = 13;
const int BUZZER_PIN = 12;
const int SD_CS = 4;

// Settings
const unsigned long ALARM_DURATION = 5000;
const int SENSITIVITY_THRESHOLD = 3;
const unsigned long LOG_INTERVAL = 5000;  // Log every 5 seconds

// Variables
bool alarmActive = false;
unsigned long alarmStartTime = 0;
int motionCount = 0;
unsigned long lastLogTime = 0;
File logFile;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(9600);
  
  // Initialize SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD initialization failed!");
    return;
  }
  
  // Create new log file
  char filename[15];
  sprintf(filename, "log_%lu.csv", millis());
  logFile = SD.open(filename, FILE_WRITE);
  
  if (logFile) {
    logFile.println("timestamp,event,sensor_state,alarm_state");
    logFile.close();
    Serial.print("Logging to: ");
    Serial.println(filename);
  } else {
    Serial.println("Error opening log file!");
  }
  
  // PIR Sensor Warm-up
  delay(60000);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Motion detection
  if (digitalRead(PIR_PIN) == HIGH) {
    handleMotionDetection(currentMillis);
  } else if (alarmActive && (currentMillis - alarmStartTime >= ALARM_DURATION)) {
    deactivateAlarm(currentMillis);
  }
  
  // Periodic logging
  if (currentMillis - lastLogTime >= LOG_INTERVAL) {
    logStatus(currentMillis);
    lastLogTime = currentMillis;
  }
}

void handleMotionDetection(unsigned long timestamp) {
  motionCount++;
  
  if (!alarmActive && motionCount >= SENSITIVITY_THRESHOLD) {
    activateAlarm(timestamp);
  }
  
  if (motionCount >= SENSITIVITY_THRESHOLD) {
    motionCount = SENSITIVITY_THRESHOLD;
  }
}

void activateAlarm(unsigned long timestamp) {
  alarmActive = true;
  alarmStartTime = timestamp;
  motionCount = 0;
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  logEvent(timestamp, "ALARM ACTIVATED");
}

void deactivateAlarm(unsigned long timestamp) {
  alarmActive = false;
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  logEvent(timestamp, "Alarm deactivated");
}

void logEvent(unsigned long timestamp, const char* event) {
  logFile = SD.open("datalog.csv", FILE_WRITE);
  if (logFile) {
    logFile.print(timestamp);
    logFile.print(",");
    logFile.print(event);
    logFile.print(",");
    logFile.print("MOTION");
    logFile.print(",");
    logFile.println(alarmActive ? "ON" : "OFF");
    logFile.close();
  }
}

void logStatus(unsigned long timestamp) {
  logFile = SD.open("datalog.csv", FILE_WRITE);
  if (logFile) {
    logFile.print(timestamp);
    logFile.print(",");
    logFile.print("STATUS");
    logFile.print(",");
    logFile.print(digitalRead(PIR_PIN) == HIGH ? "MOTION" : "STILL");
    logFile.print(",");
    logFile.println(alarmActive ? "ON" : "OFF");
    logFile.close();
  }
}
