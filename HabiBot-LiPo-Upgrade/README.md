# HabiBot V1.0 - Enhanced Robotics Platform

![FCX29HNMBP3TI2G](https://github.com/user-attachments/assets/194f79cc-0a82-4882-a770-a11f3380ec2d)
> Source Image : [HabiBot-V10](https://www.instructables.com/HabiBot-V10/) 

## Enhanced Autonomous Robot with Power System Upgrade

HabiBot V1.0 by [minhkhoitrannguyen](https://www.instructables.com/member/minhkhoitrannguyen/) is an open-source robotics platform featuring obstacle avoidance capabilities with a major power system enhancement - replacing the original 9V battery with a high-performance 7.4V LiPo battery solution. This upgrade provides **3x longer runtime** and more reliable power delivery for continuous operation.

## Key Features
- **Advanced Power System**: 7.4V 2000mAh LiPo battery with voltage monitoring
- **Extended Runtime**: 45-90 minutes continuous operation (vs 15-20 min with 9V)
- **Safety Protections**: Low-voltage cutoff and thermal monitoring
- **Obstacle Avoidance**: HC-SR04 ultrasonic sensor navigation
- **Modular Design**: 3D-printed chassis with customizable components
- **Real-time Monitoring**: Battery voltage telemetry via serial interface

## Technical Specifications
| Parameter | Specification |
|-----------|---------------|
| Microcontroller | Arduino Nano |
| Power Source | 2S 7.4V LiPo (1000-2000mAh) |
| Motors | SG90 Servos (x2) |
| Sensors | HC-SR04 Ultrasonic |
| Max Speed | 0.3 m/s |
| Runtime | 45-90 minutes |
| Dimensions | 120 × 100 × 80 mm |
| Weight | 250g (with battery) |

## Getting Started

### Prerequisites
- Arduino IDE 2.x
- 3D Printer (PLA filament)
- Basic soldering equipment

### Installation
1. Clone repository:
   ```bash
   git clone https://github.com/Customize5773/Arduino-School-Project/HabiBot-LiPo-Upgrade.git
   ```
2. Install required libraries:
   - Servo.h (included with Arduino IDE)
   
3. Upload firmware:
   ```bash
   cd HabiBot-LiPo-Upgrade/firmware
   open HabiBot_V1.0.ino
   ```

### Assembly
1. Print 3D models from `3d_models/` directory
2. Follow wiring diagram in `hardware/wiring_diagram.png`
3. Refer to [assembly guide](docs/assembly_notes.md) for LiPo installation

## Bill of Materials
Full component list with sourcing guide:  
[hardware/BOM.md](hardware/BOM.md)

**Core Components Cost: $65-95**  
*(Complete build with LiPo upgrade)*

## Safety First!
**Critical LiPo Handling Requirements:**
- Always use fireproof charging bags
- Never charge unattended
- Maintain storage voltage (3.7-3.9V/cell)
- Disconnect after use

Full safety protocol: [docs/LiPo_safety.md](docs/LiPo_safety.md)

## Usage Examples
```cpp
// Sample battery monitoring code
float voltage = readBatteryVoltage();

if(voltage < 7.0) {
  blinkWarningLED();  // Low battery alert
}

if(voltage < 6.6) {
  emergencyStop();    // Critical shutdown
}
```

## Roadmap
- [x] LiPo power system integration
- [ ] Wireless remote control module
- [ ] Solar charging capability
- [ ] ROS compatibility
- [ ] Computer vision add-on
