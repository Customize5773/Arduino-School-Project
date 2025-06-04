#pragma once
#include <Arduino.h>
#include "config.h"

volatile uint16_t fanRPM = 0;
volatile unsigned long pulseCount = 0;
unsigned long lastRpmCalcTime = 0;

void IRAM_ATTR fanTachISR() {
  pulseCount++;
}

void setupFanControl() {
  pinMode(FAN_PWM_PIN, OUTPUT);
  analogWriteFreq(PWM_FREQ);
  analogWrite(FAN_PWM_PIN, 0);  // Start with fan off
  
  // Setup tachometer interrupt if used
  #ifdef FAN_TACH_PIN
  pinMode(FAN_TACH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FAN_TACH_PIN), fanTachISR, FALLING);
  #endif
}

uint8_t calculateFanSpeed(float currentTemp) {
  if (currentTemp <= MIN_TEMP) {
    return 0;
  } else if (currentTemp >= MAX_TEMP) {
    return 100;
  } else {
    // Linear speed increase between min/max temps
    return map(currentTemp * 100, MIN_TEMP * 100, MAX_TEMP * 100, 
              FAN_MIN_PWM, 100);
  }
}

void setFanSpeed(uint8_t speedPercent) {
  uint8_t pwmValue = map(speedPercent, 0, 100, 0, 255);
  analogWrite(FAN_PWM_PIN, pwmValue);
}

uint16_t getFanRPM() {
  #ifdef FAN_TACH_PIN
  if (millis() - lastRpmCalcTime > RPM_UPDATE_INTERVAL) {
    detachInterrupt(digitalPinToInterrupt(FAN_TACH_PIN));
    fanRPM = (pulseCount * 60) / 2;  // 2 pulses per revolution
    pulseCount = 0;
    lastRpmCalcTime = millis();
    attachInterrupt(digitalPinToInterrupt(FAN_TACH_PIN), fanTachISR, FALLING);
  }
  return fanRPM;
  #else
  return 0;
  #endif
}