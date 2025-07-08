# SmartBrake-IR: Enhanced Vehicle Backup System

![FB2TS04MBP3SIBX](https://github.com/user-attachments/assets/ef3363a1-e9a9-4009-b63b-39b7b1563121)
![FR0HMLAMBP3SIMM](https://github.com/user-attachments/assets/6ad18def-8cf6-4dcc-a6a2-fac87f5b48b4)
![FETEEE9MBP3SIIZ](https://github.com/user-attachments/assets/ed2933ca-becd-47e8-9ee7-8a3a94b729d4)

> By [vithushanvijey](https://www.instructables.com/member/vithushanvijey/)

*Intelligent obstacle detection with automatic braking*

## Overview
SmartBrake-IR is an advanced Arduino-based backup sensor system that combines precise infrared distance sensing with automatic braking capabilities. Designed as an upgrade to traditional ultrasonic sensors, this project provides reliable obstacle detection and emergency response for vehicles, robotics, and industrial applications.

## Key Features ✨
- **Precise IR Sensing** - Sharp GP2Y0A21YK0F sensor for accurate 4-30" detection
- **Auto-Braking System** - Relay-controlled emergency braking at critical distances
- **Visual & Audible Alerts** - RGB LED status indicators + variable-pitch buzzer
- **Automotive-Grade Design** - 12V vehicle integration with ignition safety
- **Intelligent Thresholds** - Multi-stage warnings based on proximity

## Hardware Upgrades 🚀
| Original Component | SmartBrake-IR Upgrade |
|--------------------|-----------------------|
| HC-SR04 Ultrasonic | **Sharp GP2Y0A21YK0F IR Sensor** |
| Passive Buzzer | **PWM-Controlled Active Buzzer** |
| USB Power | **12V-to-5V Buck Converter** |
| Manual Operation | **Ignition-Activated Toggle Switch** |
| Warning Only | **5V Relay Auto-Braking System** |

## Repository Structure
```
SmartBrake-IR/
├── Hardware/            # Circuit diagrams & BOM
├── Firmware/            # Arduino source code
├── Documentation/       # Setup guide & safety notes
├── Media/               # Demo videos & photos
├── LICENSE              # MIT License
└── README.md            # This overview
```

## Quick Start Guide 🚦
1. **Hardware Setup**  
   ```bash
   git clone https://github.com/yourusername/SmartBrake-IR.git
   ```
   - Follow [Hardware/schematic.pdf](Hardware/schematic.pdf) for wiring
   
2. **Upload Code**  
   - Open `Firmware/SmartBrake_IR/SmartBrake_IR.ino` in Arduino IDE
   - Select Arduino Uno board
   - Upload to microcontroller

3. **Calibrate & Test**  
   ```arduino
   // Adjust thresholds in code:
   const float CRITICAL_DIST = 5.0;   // Brake activation distance
   const float WARNING_DIST = 10.0;   // Fast alert distance
   const float SAFE_DIST = 20.0;      // Normal operation threshold
   ```

## Safety Notice ⚠️
**This is not a road-certified safety system!**  
Always follow [safety guidelines](Documentation/safety_notes.md) during installation and testing. Never operate on public roadways without professional certification.

## License 📄
Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

---
**Ready to build?** → [Full Setup Guide](Documentation/setup_guide.md) | [Bill of Materials](Hardware/BOM.md)
