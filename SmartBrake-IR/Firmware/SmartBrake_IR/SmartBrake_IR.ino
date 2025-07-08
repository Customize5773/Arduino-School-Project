// SmartBrake_IR - Enhanced Backup Sensor with IR & Auto-Braking by vithushanvijey in instructables.com
// Upgrades: 
//  1. Sharp GP2Y0A21YK0F IR Distance Sensor
//  2. Relay for automatic braking
//  3. Power switch support

// Pin Definitions
const int IR_SENSOR = A0;     // Sharp IR sensor analog pin
const int RELAY = 12;         // Relay control for auto-braking
const int BUZZER = 13;        // Buzzer pin
const int RED = 9;            // RGB LED pins
const int GREEN = 10;
const int BLUE = 11;

// Configuration
const float CRITICAL_DIST = 5.0;   // 5 inches (activate brake)
const float WARNING_DIST = 10.0;   // 10 inches (warning zone)
const float SAFE_DIST = 20.0;      // 20 inches (safe zone)

void setup() {
  // Initialize pins
  pinMode(IR_SENSOR, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  // Start with safety defaults
  digitalWrite(RELAY, LOW);       // Brake OFF
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);      // Start in safe state (green)
  digitalWrite(BLUE, LOW);
  noTone(BUZZER);
  
  Serial.begin(9600);
  Serial.println("SmartBrake-IR System Ready");
}

void loop() {
  // 1. Read distance from IR sensor
  float distance = getDistance();
  
  // 2. Print diagnostics (optional)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" in");
  
  // 3. Control system based on distance
  if (distance < CRITICAL_DIST) {
    criticalAlert();    // Activate brake + fast alerts
  } 
  else if (distance < WARNING_DIST) {
    warningAlert();     // Fast alerts (no brake)
  } 
  else if (distance < SAFE_DIST) {
    cautionAlert();     // Slow alerts
  } 
  else {
    safeState();        // Normal operation
  }
}

// Convert IR sensor reading to inches
float getDistance() {
  int raw = analogRead(IR_SENSOR);
  if (raw <= 20) raw = 21;  // Prevent division errors
  
  // Convert analog reading to inches (calibrated for GP2Y0A21YK0F)
  float volts = raw * (5.0 / 1023.0);
  float distance_cm = 27.728 * pow(volts, -1.2045);  // Datasheet formula
  return distance_cm * 0.3937;  // Convert cm to inches
}

// ---- Alert Functions ---- //
void safeState() {
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(RELAY, LOW);   // Ensure brake OFF
  noTone(BUZZER);
  delay(100);  // Sampling stability
}

void cautionAlert() {
  // Slow pulsing blue light + beeps
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(RELAY, LOW);
  
  tone(BUZZER, 800);
  delay(300);
  noTone(BUZZER);
  delay(700);
}

void warningAlert() {
  // Fast red pulses + beeps
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(RELAY, LOW);
  
  tone(BUZZER, 1200);
  delay(150);
  noTone(BUZZER);
  delay(150);
}

void criticalAlert() {
  // Solid red + continuous tone + activate brake
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(RELAY, HIGH);  // Engage brake!
  
  tone(BUZZER, 1500);
  delay(50);  // Minimal delay for responsiveness
}
