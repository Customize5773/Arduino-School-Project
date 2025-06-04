#pragma once

// Pin Configuration
#define OLED_SDA_PIN D2
#define OLED_SCL_PIN D3
#define TEMP_SENSOR_PIN D4
#define FAN_PWM_PIN D1      // GPIO5 supports 25kHz PWM
#define FAN_TACH_PIN D5     // Optional RPM sensing

// Temperature Settings
const float MIN_TEMP = 25.0;   // Fan starts at this temperature (°C)
const float MAX_TEMP = 60.0;   // Fan runs at 100% at this temperature
const uint8_t FAN_MIN_PWM = 20;  // Minimum PWM % to prevent stall

// Fan Control Parameters
const uint32_t PWM_FREQ = 25000;  // 25kHz for PWM fans
const uint16_t RPM_UPDATE_INTERVAL = 1000;  // RPM sampling period (ms)

// Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C