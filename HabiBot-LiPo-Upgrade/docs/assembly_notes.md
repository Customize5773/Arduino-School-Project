# HabiBot (V1.0) LiPo Power Conversion

## Required Tools
- Soldering iron (30-40W)
- Wire strippers
- Multimeter
- Heat shrink tubing (3mm)
- Phillips #0 screwdriver

## Step-by-Step Modification

### 1. Remove Existing Power System
```diff
- Disconnect 9V battery clip
- Desolder barrel jack from Arduino Nano
```

### 2. Install Voltage Monitoring Circuit
```
LiPo+ → 10kΩ resistor → A0 pin
                │
               10kΩ resistor
                │
LiPo- → ────────┘
```
> **Note**: Verify voltage with multimeter (A0 should read 1/2 battery voltage)

### 3. Connect LiPo to Arduino
```arduino
LiPo+ → Arduino Vin
LiPo- → Arduino GND
```
- Use 18AWG wire minimum
- Add XT30 connector between battery and Arduino

### 4. Secure Battery Mount
1. Print `battery_tray.stl` in flexible TPU
2. Attach with M3x8mm screws to chassis
3. Use hook-and-loop tape for battery retention

### 5. Software Calibration
Upload this calibration sketch before main firmware:
```cpp
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  int raw = analogRead(A0);
  float voltage = raw * (5.0 / 1023.0) * 2.0;
  Serial.print("Raw: "); Serial.print(raw);
  Serial.print(" | Voltage: "); Serial.println(voltage);
  delay(500);
}
```
> Adjust `VOLTAGE_DIV_RATIO` in firmware if readings differ >0.1V from multimeter

## Testing Procedure
1. **Safety Check**
   - Verify no short circuits with multimeter (continuity test)
   - Check polarity 3x before first connection

2. **Power-On Test**
   - Connect battery → LED should blink once
   - Measure current draw: Should be <50mA idle

3. **Runtime Validation**
   - Record operating time until shutdown (expected: 45-90 mins)
   - Confirm low-voltage cutoff activates at 6.6V

## Troubleshooting
| Issue | Solution |
|-------|----------|
| No power | Check XT30 connection → Verify soldering |
| Voltage reading mismatch | Re-calculate voltage divider ratio |
| Servo jitter | Add 100μF capacitor across servo power |
| Premature shutdown | Calibrate `MIN_VOLTAGE` in firmware |
| Battery draining when off | Install master power switch |

## Recommended Upgrades
- Add power switch between battery positive and Vin
- Install JST-XH balance lead for easier charging
- Apply liquid electrical tape to exposed connections
