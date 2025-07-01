// Pins configuration
const int PIR_PIN = 2;
const int LED_PIN = 13;
const int BUZZER_PIN = 12;

// Settings
const unsigned long ALARM_DURATION = 5000;      // 5 seconds
const int SENSITIVITY_THRESHOLD = 3;            // Minimum triggers to activate
const unsigned long PIR_WARMUP_DURATION = 60000; // 60s calibration
const unsigned long PIR_DEBOUNCE_INTERVAL = 100; // 100ms debounce
const unsigned long ALARM_COOLDOWN = 3000;      // 3s cooldown after alarm

// Variables
bool alarmActive = false;
unsigned long alarmStartTime = 0;
int motionCount = 0;
unsigned long lastPirTriggerTime = 0;
unsigned long lastAlarmEndTime = 0;
bool lastPirState = LOW;

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
  delay(PIR_WARMUP_DURATION);  // Use const for warm-up
  Serial.println("System ready");
}

void loop() {
  unsigned long currentMillis = millis();

  // Cooldown: ignore triggers during cooldown after alarm
  if (!alarmActive && (currentMillis - lastAlarmEndTime < ALARM_COOLDOWN)) {
    // Do nothing during cooldown
    return;
  }

  bool pirState = digitalRead(PIR_PIN);

  // Debounce PIR input
  if (pirState != lastPirState) {
    lastPirTriggerTime = currentMillis;
    lastPirState = pirState;
  }

  if (pirState == HIGH && (currentMillis - lastPirTriggerTime) >= PIR_DEBOUNCE_INTERVAL) {
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
  lastAlarmEndTime = timestamp; // Start cooldown

  Serial.print(timestamp);
  Serial.println(" | Alarm deactivated");
}
