#include <DHT.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

const int RGB1[] = {9, 10, 11};
const int RGB2[] = {5, 6, 7};

const int SOIL_ANALOG = A0;
const int SOIL_DIGITAL = 8;

const int SOUND_PIN = 3;
const int RED_LED = 2;
const int LED_13 = 13;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};
byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {39, 41, 43, 45};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int displayMode = 1;
unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 2000;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  
  for(int i=0; i<3; i++) {
    pinMode(RGB1[i], OUTPUT);
    pinMode(RGB2[i], OUTPUT);
  }
  
  pinMode(SOIL_DIGITAL, INPUT);
  pinMode(SOUND_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(LED_13, OUTPUT);
  
  lcd.print("System Ready");
  delay(1500);
  lcd.clear();
}

void loop() {
  handleSoundSensor();
  handleKeypad();
  
  if(millis() - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = millis();
    updateSensors();
  }
}

void handleSoundSensor() {
  int soundValue = digitalRead(SOUND_PIN);
  digitalWrite(RED_LED, soundValue);
  digitalWrite(LED_13, soundValue);
}

void handleKeypad() {
  char key = keypad.getKey();
  
  if(key == '1') {
    displayMode = 1;
    lcd.clear();
  } 
  else if(key == '2') {
    displayMode = 2;
    lcd.clear();
  }
}

void updateSensors() {
  float temp = dht.readTemperature(true);
  float humid = dht.readHumidity();
  int soilRaw = analogRead(SOIL_ANALOG);
  int soilPercent = constrain(map(soilRaw, 1023, 300, 0, 100), 0, 100);
  int soilState = digitalRead(SOIL_DIGITAL);
  
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" | Humid: "); Serial.print(humid);
  Serial.print(" | Soil: "); Serial.print(soilPercent);
  Serial.print("% | State: "); Serial.print(soilState ? "Dry" : "Wet");
  Serial.print(" | Sound: "); Serial.println(digitalRead(SOUND_PIN));
  
  if(displayMode == 1) {
    displaySoilMoisture(soilPercent);
    setRGB(RGB2, soilPercent);
  } 
  else if(displayMode == 2) {
    displayClimate(temp, humid);
    setRGB(RGB1, temp);
  }
}

void displaySoilMoisture(int percent) {
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture");
  lcd.setCursor(0, 1);
  lcd.print("Level: ");
  lcd.print(percent);
  lcd.print("%");
}

void displayClimate(float temp, float humid) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.write(223);
  lcd.print("F");
  
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humid);
  lcd.print("%");
}

void setRGB(const int pins[3], float value) {
  if(pins == RGB1) {  // Temperature mode
    if(value < 70) writeRGB(pins, 0, 0, 255);
    else if(value > 75) writeRGB(pins, 255, 0, 0);
    else writeRGB(pins, 0, 255, 0);
  } 
  else {  // Soil moisture mode
    if(value < 50) writeRGB(pins, 255, 0, 0);
    else if(value <= 75) writeRGB(pins, 0, 255, 0);
    else writeRGB(pins, 0, 0, 255);
  }
}

void writeRGB(const int pins[3], int r, int g, int b) {
  analogWrite(pins[0], r);
  analogWrite(pins[1], g);
  analogWrite(pins[2], b);
}
