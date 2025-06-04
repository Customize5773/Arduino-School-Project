#pragma once
#include <Wire.h>
#include <SSD1306Wire.h>
#include "config.h"

SSD1306Wire display(OLED_ADDRESS, OLED_SDA_PIN, OLED_SCL_PIN);

void initDisplay() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void updateDisplay(float currentTemp, uint8_t fanSpeed, uint16_t rpm = 0) {
  display.clear();
  
  // Temperature display
  display.drawString(0, 0, "Temperature: ");
  display.drawString(70, 0, String(currentTemp, 1) + " C");
  
  // Fan speed display
  display.drawString(0, 16, "Fan Speed: ");
  display.drawString(70, 16, String(fanSpeed) + "%");
  
  // RPM display (if available)
  if (rpm > 0) {
    display.drawString(0, 32, "Fan RPM: ");
    display.drawString(70, 32, String(rpm));
  }
  
  // Temperature scale visualization
  display.drawString(0, 48, "|----|----|----|----|");
  int tempPos = map(constrain(currentTemp, MIN_TEMP, MAX_TEMP), 
                  MIN_TEMP, MAX_TEMP, 0, 100);
  display.fillRect(tempPos, 46, 3, 10);
  
  display.display();
}
