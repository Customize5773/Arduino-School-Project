#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#define trigPin 5 // Trigger pin for the ultrasonic sensor
#define echoPin 4 // Echo pin for the ultrasonic sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD 16x2
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // Initialize infrared temperature sensor

const byte DEGREE_SYMBOL = B11011111; // Degree symbol for displaying temperature
int counter = 0; // Counter for the number of people entering
int currentState = 0; // Current state of detection
int previousState = 0; // Previous state of detection

long duration, distance; // Variables for ultrasonic sensor: pulse duration and calculated distance

void setup() {
  Serial.begin(9600); // Initialize serial communication
  lcd.backlight(); // Turn on LCD backlight
  lcd.init(); // Initialize the LCD
  mlx.begin(); // Start the temperature sensor
  pinMode(trigPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT); // Set echo pin as input
}

void loop() {
  // Print ambient and object temperature to the serial monitor
  Serial.print("Ambient Temperature = ");
  Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject Temperature = ");
  Serial.print(mlx.readObjectTempC());
  Serial.println("*C");

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Measure the pulse duration
  distance = (duration / 2) / 29.1; // Convert duration to distance (in cm)

  // Display distance on the serial monitor
  Serial.print("Distance (HC-SR04) = ");
  Serial.print(distance);
  Serial.println(" cm");

  // Update the LCD display
  lcd.setCursor(0, 0);
  lcd.print("People Entered: ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.setCursor(7, 1);
  lcd.print(mlx.readObjectTempC() * 1.090); // Temperature reading with calibration factor
  lcd.setCursor(12, 1);
  lcd.write(DEGREE_SYMBOL); // Degree symbol
  lcd.setCursor(13, 1);
  lcd.print("C"); // Celsius unit

  // If the temperature is above 38°C, display a fever alert on the LCD
  if (mlx.readObjectTempC() * 1.090 > 38) {
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("WARNING!");
    lcd.setCursor(4, 1);
    lcd.print("FEVER!!!");
    delay(4000);
    lcd.clear();
  }

  // If the distance is less than 50 cm, set the detection state
  if (distance <= 50) {
    currentState = 1;
  } else {
    currentState = 0;
  }

  // If the detection state changes, increment the counter
  if (currentState != previousState) {
    if (currentState == 1) {
      counter = counter + 1; // Increment people count
      lcd.setCursor(13, 0);
      lcd.print(counter);
      Serial.print("PEOPLE ENTERED = ");
      Serial.print(counter);
    }
  }
  previousState = currentState; // Update the previous state
}
