# Temperature Controlled PWM Fan System with Arduino

Automated fan speed control system using Arduino (Wemos D1 Mini) that dynamically adjusts PWM fan speed based on temperature readings. Perfect for PC cooling, server racks, and electronics projects!

## Features 
- Real-time temperature monitoring with DS18B20 sensor
- 25kHz PWM control for PC fans (silent operation)
- OLED display showing temp/speed/RPM
- Automatic speed adjustment between configurable thresholds
- MOSFET-based power control (supports multiple fans)
- Safety features: Sensor failure detection, fan stall prevention
- WiFi monitoring (Wemos D1 Mini)

## Hardware Requirements 🛠️
[![BOM](https://img.shields.io/badge/View_Full_BOM-bill_of_materials.md-blue)](hardware/bill_of_materials.md)

| Component | Quantity | Notes |
|-----------|----------|-------|
| Wemos D1 Mini | 1 | ESP8266 development board |
| 4-Pin PWM Fan | 1+ | 120mm PC fan recommended |
| DS18B20 Sensor | 1 | Waterproof version |
| IRLB8721 MOSFET | 1 per fan | Logic-level gate |
| 0.96" OLED Display | 1 | I2C interface |
| 4.7kΩ Resistor | 1 | For temperature sensor |

> Full BOM available in [hardware/bill_of_materials.md](hardware/bill_of_materials.md)

## Wiring

| Component     | Wemos Pin | Connection Note       |
|---------------|-----------|-----------------------|
| OLED SDA      | D2        |                       |
| OLED SCL      | D3        |                       |
| DS18B20 Data  | D4        | 4.7kΩ pull-up to 3.3V |
| Fan PWM       | D1        | Gate of MOSFET        |
| Fan Power     | -         | 12V via MOSFET drain  |

> Detailed wiring guide in [PWM Setup Documentation](docs/pwm_setup.md)

## Configuration ⚙️
Edit `firmware/config.h` to customize:
```cpp
// Temperature Settings
const float MIN_TEMP = 25.0;   // Fan starts at this temperature (°C)
const float MAX_TEMP = 60.0;   // Fan runs at 100% at this temperature
const uint8_t FAN_MIN_PWM = 20;  // Minimum PWM % to prevent stall

// Fan Control
const uint32_t PWM_FREQ = 25000;  // 25kHz for PWM fans
```

## Usage 🚀
1. Power on the system
2. Observe temperature and fan speed on OLED display
3. System automatically adjusts fan speed:
   - Below MIN_TEMP: Fan off
   - Above MAX_TEMP: 100% speed
   - Between thresholds: Proportional speed

## Calibration Guide 🔧
For accurate temperature readings:
1. Perform ice bath (0°C) and boiling water (100°C) tests
2. Adjust calibration offset in code:
```cpp
// In temperature_sensor.h
float calibrationOffset = 0.0;  // Adjust this value
```
> Full calibration instructions in [Calibration Guide](docs/calibration_guide.md)

## Troubleshooting 
| Symptom | Possible Fix |
|---------|--------------|
| Fan not spinning | Check MOSFET connections, verify PWM signal |
| Temperature reading -127°C | Check DS18B20 wiring and pull-up resistor |
| OLED not displaying | Verify I2C address (usually 0x3C) |
| Fan runs at full speed | Confirm PWM frequency is set to 25kHz |
