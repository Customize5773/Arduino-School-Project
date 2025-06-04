#include "config.h"
#include "display_manager.h"
#include "fan_controller.h"
#include "temperature_sensor.h"

unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 2000;  // Update every 2 seconds

void setup() {
  Serial.begin(115200);
  
  // Initialize components
  initTemperatureSensor();
  setupFanControl();
  initDisplay();
  
  // Initial display message
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 24, "System Starting");
  display.display();
  delay(1000);
  
  Serial.println("System initialized");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastUpdateTime >= UPDATE_INTERVAL) {
    lastUpdateTime = currentMillis;
    
    // Read temperature
    float currentTemp = getTemperature();
    
    // Calculate and set fan speed
    uint8_t fanSpeed = calculateFanSpeed(currentTemp);
    setFanSpeed(fanSpeed);
    
    // Get fan RPM (if tachometer connected)
    uint16_t fanRPM = getFanRPM();
    
    // Update display
    updateDisplay(currentTemp, fanSpeed, fanRPM);
    
    // Serial monitor output
    Serial.print("Temperature: ");
    Serial.print(currentTemp, 1);
    Serial.print("°C | Fan Speed: ");
    Serial.print(fanSpeed);
    Serial.print("%");
    if (fanRPM > 0) {
      Serial.print(" | RPM: ");
      Serial.print(fanRPM);
    }
    Serial.println();
  }
  
  // Handle sensor errors
  if (getTemperature() < -90) {
    display.clear();
    display.drawString(0, 24, "SENSOR ERROR!");
    display.display();
    setFanSpeed(100);  // Full speed for safety
    delay(1000);
  }
}
