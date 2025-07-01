/* PIR Sensor with Buzzer and Data Logging
 * Features:
 * 1. Non-blocking timing with millis()
 * 2. Dual output (LED + buzzer)
 * 3. Serial data logging with timestamps
 * 4. False trigger prevention
 * 5. Configurable sensitivity
 */

// Pins configuration
const int PIR_PIN = 2;
const int LED_PIN = 13;
const int BUZZER_PIN = 12;

// Settings
const unsigned long ALARM_DURATION = 5000;  // 5 seconds
const int SENSITIVITY_THRESHOLD = 3;        // Minimum triggers to activate

// Variables
bool alarmActive = false;
unsigned long alarmStartTime = 0;
int motionCount = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("System initialized");
  Serial.println("Timestamp (ms) | Event");
  Serial.println("--------------------------");
  
  // PIR Sensor Warm-up
  Serial.println("Calibrating sensor...");
  delay(60000);  // 60s calibration
  Serial.println("System ready");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (digitalRead(PIR_PIN) == HIGH) {
    handleMotionDetection(currentMillis);
  } else if (alarmActive && (currentMillis - alarmStartTime >= ALARM_DURATION)) {
    deactivateAlarm(currentMillis);
  }
}

void handleMotionDetection(unsigned long timestamp) {
  motionCount++;
  
  if (!alarmActive && motionCount >= SENSITIVITY_THRESHOLD) {
    activateAlarm(timestamp);
  }
  
  // Reset count if no continuous motion
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
  
  Serial.print(timestamp);
  Serial.println(" | ALARM ACTIVATED");
}

void deactivateAlarm(unsigned long timestamp) {
  alarmActive = false;
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.print(timestamp);
  Serial.println(" | Alarm deactivated");
}
