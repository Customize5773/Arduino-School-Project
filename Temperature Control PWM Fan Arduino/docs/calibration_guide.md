# Temperature Sensor Calibration Guide

## Why Calibrate?
DS18B20 sensors typically have ±0.5°C accuracy, but environmental factors and manufacturing variations can cause offsets. Calibration ensures:
1. Accurate temperature readings
2. Proper fan activation thresholds
3. Consistent system performance

## Equipment Needed
1. Reference thermometer (mercury or certified digital)
2. Glass of ice water (0°C reference)
3. Boiling water (100°C reference at sea level)
4. Small screwdriver (for potentiometer adjustment if using analog sensors)

## Step-by-Step Calibration

### 1. Two-Point Calibration (Recommended)
```cpp
// In temperature_sensor.h
float calibrationOffset = 0.0;  // Adjust this value

float getTemperature() {
  // ... existing code ...
  return tempC + calibrationOffset;  // Add offset to readings
}
```

**Procedure**:
a. **0°C Test**:
   - Submerge sensor in ice bath (50% ice + 50% water)
   - Wait 2 minutes for stabilization
   - Record sensor reading (e.g., -0.3°C)
   - Calculate offset: `calibrationOffset = 0.0 - (-0.3) = +0.3`

b. **100°C Test**:
   - Boil water at sea level (adjust +0.5°C per 300m elevation)
   - Record sensor reading (e.g., 98.7°C)
   - Calculate average offset: `(0.3 + (100.0 - 98.7)) / 2 = +0.8`

### 2. Single-Point Calibration
If you can only test at room temperature:
1. Place reference thermometer and DS18B20 side-by-side
2. Wait 30 minutes for thermal equilibrium
3. Calculate: `calibrationOffset = referenceTemp - sensorReading`

### 3. Multi-Sensor Consistency (For Arrays)
1. Place all sensors in same environment
2. Identify average reading
3. Set offsets so all sensors match average:
```cpp
// For 3 sensors with readings [22.1, 22.5, 22.3]
float offsets[] = {+0.2, -0.2, 0.0};
```

## Advanced Compensation
For nonlinear errors (rarely needed):
```cpp
// In temperature_sensor.h
float linearCorrection(float rawTemp) {
  return (rawTemp * 1.02) - 0.5;  // Example: scale + offset
}
```

## Validation Process
1. After calibration, test at three points:
   - Low (0-20°C)
   - Mid (20-40°C)
   - High (60-80°C)
2. Allow 5 minutes stabilization per test
3. Acceptable tolerance: ±0.5°C from reference

## Common Issues & Fixes
| **Problem**               | **Solution**                          |
|---------------------------|---------------------------------------|
| Readings fluctuate ±2°C   | Add 100nF capacitor between data and GND |
| Sensor reports -127°C     | Check wiring, 4.7kΩ pull-up resistor |
| Consistent +3°C offset    | Verify against reference thermometer |
| Different sensors disagree| Implement per-sensor offsets in code |

## Factory Calibration Notes
1. DS18B20s are laser-trimmed at factory
2. Re-calibration typically needed only for:
   - Precision applications (±0.1°C)
   - Extreme temperature ranges
   - Long cable runs (>20m)

> **Safety Tip**: Never calibrate above 100°C without Teflon-insulated sensors
