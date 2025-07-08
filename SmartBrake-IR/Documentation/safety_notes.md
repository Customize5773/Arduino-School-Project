# Safety Notes: SmartBrake-IR System

⚠️ **WARNING: This project involves potentially dangerous electrical systems and moving vehicle components. Exercise extreme caution during installation and operation.**

## Electrical Safety Precautions

### 1. Relay and Braking System Safety
- **Isolation Requirement**:
  - Maintain complete electrical isolation between Arduino (5V) and vehicle systems (12V)
  - Use opto-isolated relays only (recommended: [HLS8L-DC5V-S-C](https://www.amazon.com/dp/B07BVXT1ZK))
  - Never directly connect Arduino pins to vehicle wiring

- **Fusing Protection**:
  ```mermaid
  graph LR
    A[Vehicle Battery] --> B[5A Fuse] --> C[Relay] --> D[Brake Actuator]
    E[Arduino] -->|Control Signal| C
  ```
  - Install 5A fuse on ALL 12V power connections
  - Place fuse within 7 inches of power source

- **Relay Specifications**:
  - Must support at least 10A @ 12V DC
  - Use automotive-grade relays only (not breadboard relays)
  - Secure relay connections with crimp connectors, not solder alone

### 2. Power System Safety
- **Voltage Conversion**:
  - Use only automotive-certified DC-DC converters (e.g., [DROK 12V to 5V](https://www.amazon.com/dp/B01GJZF31W))
  - Verify converter has:
    - Over-voltage protection
    - Short-circuit protection
    - Thermal shutdown

- **Wiring Standards**:
  - Use 18AWG wire minimum for 12V connections
  - Protect all wires with split loom tubing
  - Secure wires away from moving parts (steering column, pedals)

## Automotive Integration Warnings

### 1. Braking System Precautions
- **TEST IN SAFE ENVIRONMENT FIRST**
  - Only test on private property with no obstacles
  - Maximum test speed: 5 MPH
  - Have emergency manual override available

- **Do NOT connect to primary brake system**
  - Only interface with secondary/auxiliary braking systems
  - For demonstration vehicles only (not roadworthy vehicles)

### 2. Sensor Placement Guidelines
- Mount IR sensor:
  - Minimum 12 inches from ground
  - Protected from direct road debris
  - Periodically clean sensor lens (monthly)

- Avoid mounting near:
  - Exhaust systems
  - Heat sources
  - Moving suspension components

## General Safety Practices

### 1. Installation Checklist
1. Disconnect vehicle battery before installation
2. Verify all connections with multimeter before power-on
3. Securely mount all components (no loose boards/wires)
4. Apply dielectric grease to all exposed connectors
5. Test system without vehicle movement first

### 2. Operational Limitations
- **Not for real-world driving**:
  ```diff
  + Acceptable: Golf carts, robotics projects, demonstration rigs
  - Unacceptable: Street vehicles, highway use, commercial vehicles
  ```
- Environmental limitations:
  - Do not operate in rain/wet conditions
  - Temperature range: 32°F to 122°F (0°C to 50°C)
  - Avoid direct sunlight on electronics

### 3. Maintenance Schedule
| Component       | Check Frequency | Maintenance Action |
|-----------------|-----------------|--------------------|
| IR Sensor       | Monthly         | Clean lens with isopropyl alcohol |
| Wiring          | Quarterly       | Inspect for chafing/damage |
| Relay Contacts  | Biannually      | Check for pitting/arcing |
| Power Converter | Annually        | Verify output voltage (5V ±0.25V) |

## Emergency Procedures

### If system malfunctions:
1. Immediately flip power switch to OFF position
2. Disconnect vehicle battery
3. Check for:
   - Burning smell
   - Smoke
   - Unusual heat from components
4. Do not reconnect until fault is identified
