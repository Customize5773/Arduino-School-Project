// Define pin numbers for the ultrasonic sensor
const int trigPin = 9; // Trigger pin for the ultrasonic sensor
const int echoPin = 10; // Echo pin for the ultrasonic sensor

// Define pin numbers for other components
const int clapLampPin = 8; // Pin for the clap lamp
const int ledPin = 7; // Pin for the LED
const int soundSensorPin = A0; // Pin for the sound sensor

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  
  // Set pin modes for output and input
  pinMode(ledPin, OUTPUT); // LED output
  pinMode(soundSensorPin, INPUT_PULLUP); // Sound sensor input with pull-up resistor
  pinMode(trigPin, OUTPUT); // Trigger pin output
  pinMode(echoPin, INPUT); // Echo pin input
  pinMode(clapLampPin, OUTPUT); // Clap lamp output
}

void loop() {
  long duration, distance; // Variables for storing ultrasonic sensor data
  int sound = analogRead(soundSensorPin); // Read value from the sound sensor
  
  // Send a pulse from the ultrasonic sensor's trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the time for the echo pulse
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  // Control the LED based on the distance
  if (distance < 8) {
    digitalWrite(ledPin, LOW); // Turn off the LED if the object is too close
    delay(100000000); // Delay for an extended period
  } else if (distance > 8) {
    digitalWrite(ledPin, HIGH); // Turn on the LED if the object is far
  }
  
  // Control the clap lamp based on sound sensor input
  if (sound) {
    digitalWrite(clapLampPin, HIGH); // Turn on the lamp if sound is detected
  } else {
    digitalWrite(clapLampPin, LOW); // Turn off the lamp if no sound is detected
  }
}
