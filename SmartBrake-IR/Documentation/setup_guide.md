# SmartBrake-IR Setup Guide

## Table of Contents
1. [Hardware Components](#hardware-components)
2. [Circuit Assembly](#circuit-assembly)
3. [Power System Setup](#power-system-setup)
4. [Sensor Mounting](#sensor-mounting)
5. [Arduino IDE Configuration](#arduino-ide-configuration)
6. [Code Upload](#code-upload)
7. [Calibration](#calibration)
8. [Testing Procedure](#testing-procedure)

---

## Hardware Components
You'll need these additional components beyond the original project:
```markdown
- [ ] Sharp GP2Y0A21YK0F IR Distance Sensor
- [ ] 5V Relay Module (Opto-isolated)
- [ ] 12V-to-5V DC Buck Converter (3A minimum)
- [ ] Automotive Toggle Switch
- [ ] 5A Fuse with Holder
- [ ] 18AWG Automotive Wire (Red/Black)
- [ ] Inline Wire Connectors
```

---

## Circuit Assembly

### Connection Guide:
| Component          | Arduino Pin | Notes                          |
|--------------------|-------------|--------------------------------|
| **Sharp IR Sensor** | A0          | Yellow wire to A0              |
| **Relay Module**   | 12          | IN pin to D12                  |
| **RGB LED**        | 9,10,11     | R=9, G=10, B=11                |
| **Buzzer**         | 13          | Positive wire                  |
| **Power Switch**   | N/A         | Between battery and converter |

### Critical Wiring Steps:
1. **Power Connections**:
   ```mermaid
   graph LR
   A[Car Battery +12V] --> B[5A Fuse]
   B --> C[Toggle Switch]
   C --> D[Buck Converter Input]
   D --> E[Arduino Vin]
   ```
   
2. **Relay Wiring**:
   - Relay COM → +12V (fused)
   - Relay NO → Brake actuator positive
   - Brake actuator negative → Ground

3. **Sensor Wiring**:
   - Sharp IR Red → +5V
   - Sharp IR Black → GND
   - Sharp IR Yellow → A0

---

## Power System Setup
### Automotive Power Connection:
1. Disconnect vehicle battery negative terminal
2. Connect buck converter input:
   - **RED**: Fused 12V from battery
   - **BLACK**: Solid chassis ground
3. Connect buck converter output to Arduino:
   - **+5V** → Arduino Vin
   - **GND** → Arduino GND
4. Mount toggle switch in accessible location

> ⚠️ **Warning**: Always fuse 12V connections within 7" of power source!

---

## Sensor Mounting
### Optimal Placement:
- Rear bumper centerline
- 12-18 inches above ground
- Angled slightly downward (15°)
- Protected location (avoid license plate area)

### Mounting Steps:
1. Clean mounting surface with alcohol
2. Use 3M VHB tape for temporary mounting
3. Test detection range before permanent install
4. Secure with M3 screws and rubber washers

---

## Arduino IDE Configuration
1. Install [Arduino IDE 2.x](https://www.arduino.cc/en/software)
2. Add required libraries (none needed for core functionality)
3. Configure board settings:
   - **Board**: Arduino Uno
   - **Port**: COMx (Windows) or /dev/cu.usbmodemxx (Mac)
   - **Programmer**: AVRISP mkII

---

## Code Upload
1. Download `SmartBrake_IR.ino` from GitHub repo
2. Open file in Arduino IDE
3. Verify code (Ctrl+R)
4. Upload to Arduino (Ctrl+U)
5. Monitor serial output (Ctrl+Shift+M):
   ```plaintext
   > SmartBrake-IR System Ready
   > Distance: 15.34 in
   ```

---

## Calibration
### IR Sensor Calibration:
1. Place object at known distance (e.g., 10 inches)
2. Open Serial Monitor (Tools > Serial Monitor)
3. Note raw analog value:
   ```ino
   // Temporary calibration code:
   void setup() { Serial.begin(9600); }
   void loop() {
     Serial.print("Raw: ");
     Serial.println(analogRead(A0));
     delay(500);
   }
   ```
4. Adjust distance formula if needed:
   ```ino
   // In getDistance() function:
   return 4800.0 / (raw - 20);  // Modify constant as needed
   ```

### Threshold Adjustment:
```ino
// Change these values in the main code:
const float CRITICAL_DIST = 5.0;   // Brake activation distance
const float WARNING_DIST = 10.0;   // Fast alert distance
const float SAFE_DIST = 20.0;      // Normal operation threshold
```

---

## Testing Procedure
### Safety Checklist:
- [ ] Vehicle on level surface
- [ ] Parking brake engaged
- [ ] Wheels chocked
- [ ] No persons behind vehicle

### Test Sequence:
1. Power on system (toggle switch ON)
2. Verify startup sequence:
   - Green LED solid for 2 seconds
   - Short buzzer beep
3. Distance simulation test:
   | Distance      | Expected Response               |
   |---------------|---------------------------------|
   | >20 inches    | Steady GREEN LED                |
   | 10-20 inches  | Slow-pulsing BLUE LED + beeps   |
   | 5-10 inches   | Fast-pulsing RED LED + beeps    |
   | <5 inches     | Solid RED + continuous tone + relay click |

4. Brake activation test (only with wheels OFF ground)

> **Complete 10 test cycles before road testing**

---

## Troubleshooting
| Symptom                 | Solution                      |
|-------------------------|-------------------------------|
| No power                | Check fuse and ground points |
| Inconsistent distances  | Clean IR sensor lens         |
| Relay not activating    | Verify 12V supply to COM pin |
| Buzzer not sounding     | Check D13 connection         |
| LED colors incorrect    | Verify RGB pin assignments   |

For additional support, create an issue on the [GitHub repository](https://github.com/Customize5773/Arduino-School-Project).
