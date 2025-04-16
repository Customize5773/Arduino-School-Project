#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define Threshold 30
#define MQ2pin 0
#define BUZZER_PIN 4
const int VibrationSensor = 10;
int Siren = 5;
int SirenLedPin = 6;
int co, smoke;
float sensorValue;

DHT dht(2, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Fire Alarm");
  lcd.setCursor(0, 1);
  lcd.print("     System     ");
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Loading...  ");
  lcd.setCursor(0, 1);
  lcd.print(" > Group 5 < ");
  delay(3000);
  lcd.clear();
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(Siren, OUTPUT);
  pinMode(SirenLedPin, OUTPUT);
  pinMode(VibrationSensor, INPUT);
  dht.begin();
}

void loop() {
  int vibrationValue = digitalRead(VibrationSensor);
  
  Serial.print("Vibration: ");
  Serial.print(vibrationValue);
  
  if (vibrationValue == HIGH) {
    digitalWrite(Siren, HIGH);
    digitalWrite(SirenLedPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("EARTHQUAKE DETECTED!");
    delay(2000);
    lcd.clear();
  }
  else {
    digitalWrite(Siren, LOW);
    digitalWrite(SirenLedPin, LOW);
  }

  sensorValue = analogRead(MQ2pin);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);

  if (sensorValue > Threshold) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Smoke Detected!");
    Serial.println(" | Gas Detected!");

    tone(BUZZER_PIN, 5000, 5000);
    delay(8000);
    noTone(BUZZER_PIN);

    Serial.println("");
    delay(2000);
  }

  if (isnan(humidity) || isnan(temperature) || isnan(sensorValue)) {
    lcd.print("Failed to Read");
    Serial.println(" || Failed to Read");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.setCursor(6, 0);
  lcd.print(temperature);
  lcd.setCursor(11, 0);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.setCursor(10, 1);
  lcd.print(humidity);
  lcd.print("%\t");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("SMOKE:");
  lcd.setCursor(5, 0);
  lcd.print(sensorValue);
  lcd.setCursor(11, 0);
  lcd.print("PPM");
  delay(2000);
  lcd.clear();

  delay(50);
}
