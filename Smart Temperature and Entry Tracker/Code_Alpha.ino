#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize 16x2 LCD
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // Initialize infrared temperature sensor
//Servo myservo;

const int trigPin = 5; // Trigger pin for ultrasonic sensor
const int echoPin = 4; // Echo pin for ultrasonic sensor
//const int servoPin = 3; // Pin for servo motor
const int buzzerPin = 10; // Pin for buzzer
const int feverLampPin = 11; // Pin for fever lamp
const byte DEGREE_SYMBOL = B11011111; // ASCII symbol for the degree (°)

int peopleCount = 0; // Counter for the number of people detected
long duration; // Stores ultrasonic pulse duration
int distance; // Stores calculated distance in cm

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(trigPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT); // Set echo pin as input
  pinMode(feverLampPin, OUTPUT); // Set fever lamp pin as output
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output

  mlx.begin(); // Start the temperature sensor
  lcd.init(); // Start the LCD
  lcd.backlight(); // Enable LCD backlight
  
  //myservo.attach(servoPin); // Attach servo motor
  //myservo.write(0); // Initialize servo position to 0 degrees
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Measure pulse duration
  distance = duration * 0.034 / 2; // Calculate distance in cm

  float temp = mlx.readObjectTempC(); // Read object temperature from the sensor

  // Display people count and temperature on the LCD
  lcd.setCursor(0, 0);
  lcd.print("People Entered: ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.setCursor(7, 1);
  lcd.print(temp); // Display the temperature value
  lcd.setCursor(12, 1);
  lcd.write(DEGREE_SYMBOL); // Display degree symbol
  lcd.setCursor(13, 1);
  lcd.print("C"); // Display Celsius unit

  // Increment people count if a person is detected within 20 cm
  if (distance < 20) {
    peopleCount++;
    lcd.setCursor(13, 0);
    lcd.print(peopleCount);
    delay(2000);
  }

  // Check for fever condition and trigger buzzer and lamp
  if (temp > 37) {
    delay(50);
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("WARNING!");
    lcd.setCursor(4, 1);
    lcd.print("FEVER!!!");
    
    digitalWrite(buzzerPin, HIGH); // Activate buzzer
    digitalWrite(feverLampPin, HIGH); // Turn on fever lamp
    delay(5000); // Delay for alarm
  } else if (temp < 37) {
    digitalWrite(buzzerPin, LOW); // Deactivate buzzer
    digitalWrite(feverLampPin, LOW); // Turn off fever lamp
  }
  delay(1000); // Delay for system update
}
