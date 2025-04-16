#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD (16x2)

const int TRIG_Pin = 8; // Ultrasonic sensor trigger pin
const int ECHO_Pin = 9; // Ultrasonic sensor echo pin

const int vibrationSensorPin = 7; // Pin for vibration sensor
const int buzzerPin = 5; // Pin for buzzer
const int infraredSensorPin = 11; // Pin for infrared sensor
const int servoPin = 10; // Pin for servo motor

Servo servo; // Create a Servo object

void setup() {
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight for the LCD

  pinMode(vibrationSensorPin, INPUT); // Vibration sensor as input
  pinMode(buzzerPin, OUTPUT); // Buzzer as output
  pinMode(infraredSensorPin, INPUT); // Infrared sensor as input
  pinMode(TRIG_Pin, OUTPUT); // Trigger pin as output
  pinMode(ECHO_Pin, INPUT); // Echo pin as input

  servo.attach(servoPin); // Attach servo motor
  servo.write(0); // Initialize servo motor to 0 degree
  lcd.clear(); // Clear the LCD

  Serial.begin(9600); // Initialize serial communication

  delay(500); // Short delay for initialization
}

void loop() {
  long duration, distance;

  // Ultrasonic Sensor Program
  digitalWrite(TRIG_Pin, LOW); // Ensure trigger is off
  delayMicroseconds(2); 
  digitalWrite(TRIG_Pin, HIGH); // Trigger a 10 microsecond pulse
  delayMicroseconds(10); 
  digitalWrite(TRIG_Pin, LOW); // Turn off trigger
  duration = pulseIn(ECHO_Pin, HIGH); // Measure echo duration
  distance = (duration / 2) / 29.1; // Convert duration to distance in cm

  // LCD Program: Display "Thank You" message if distance <= 5 cm
  if (distance <= 5) {
    lcd.setCursor(2, 0);
    lcd.print("THANK YOU");
    lcd.setCursor(5, 1);
    lcd.print("SO MUCH");
    delay(1000); // Display for 1 second
    lcd.clear();
  }

  // Vibration Sensor & Buzzer Program
  int vibrationValue = digitalRead(vibrationSensorPin); // Read vibration sensor
  unsigned long startTime = millis(); // Get start time

  if (vibrationValue == HIGH) { // If vibration is detected
    Serial.print(vibrationValue);
    while (millis() - startTime < 5000) { // Buzzer activates for 5 seconds
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      delay(500);
    }
  } else if (vibrationValue == LOW) { // If no vibration
    digitalWrite(buzzerPin, LOW);
    Serial.print(vibrationValue);
  }

  // Servo Motor & Infrared Sensor Program
  int infraredValue = digitalRead(infraredSensorPin); // Read infrared sensor

  if (infraredValue == HIGH) { // If infrared sensor detects an object
    servo.write(90); // Rotate servo to 90 degrees
    delay(3000); // Hold for 3 seconds
  } else if (infraredValue == LOW) { // If no object is detected
    servo.write(0); // Rotate servo back to 0 degrees
  }
}
