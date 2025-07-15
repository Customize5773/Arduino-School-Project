# Arduino LED Chaser Game

![FQV5QGAMBP3W8MI](https://github.com/user-attachments/assets/31e1d5a2-2e40-40e8-84ad-0b85427b428c)

**Hybrid Electronics Project Combining 555 Timer, 4017 Counter & Arduino**

[Game Demo](https://www.youtube.com/embed/K8hhmg3bHwE?feature=oembed&autoplay=1)  
*Gameplay demonstration - Match the RGB color with the chasing LEDs*

## Overview
This project combines classic 555 timer circuitry with modern Arduino control to create an interactive LED chaser game. Players must press a button when the chasing LED matches the color shown on the RGB indicator. The game features adjustable difficulty, score tracking, and win/lose conditions.

**Key Features**:
- Interactive LED chasing gameplay
- RGB target color indicator
- Analog speed control via potentiometer
- Score tracking with win/lose conditions
- Hybrid analog-digital design (555 + Arduino)

## Hardware Requirements
The complete Bill of Materials is available in [docs/BOM.md](docs/BOM.md)

**Core Components**:
- Arduino Uno/Nano
- NE555 Timer IC
- CD4017 Decade Counter
- 6x LEDs (2 blue, 2 red, 2 yellow)
- Common Anode RGB LED
- 10KΩ Potentiometer
- Tactile push button
- Resistors (330Ω × 3, 1KΩ × 1, 10KΩ × 2)
- 100μF Capacitor
- Breadboard and jumper wires

## Circuit Setup

### Connection Summary:
1. **555 Timer** configured in astable mode generates clock pulses
2. **4017 Counter** sequences through 6 outputs (LED1-LED6)
3. **Arduino**:
   - Monitors LED states via digital inputs
   - Controls RGB LED via PWM outputs
   - Reads button input
4. **Potentiometer** adjusts 555 frequency (game speed)

### Wiring Guide:
| Arduino Pin | Connected To          |
|-------------|-----------------------|
| 2           | Push Button          |
| 3           | LED4 (Blue)          |
| 4           | LED1 (Blue)          |
| 5           | LED3 (Yellow)        |
| 7           | LED2 (Red)           |
| 8           | LED6 (Yellow)        |
| 9           | RGB Red Cathode      |
| 10          | RGB Green Cathode    |
| 11          | RGB Blue Cathode     |
| 13          | LED5 (Red)           |

## Installation & Setup

### 1. Hardware Assembly
Follow the breadboard layout guide: [schematics/PCB_Layout.md](schematics/PCB_Layout.md)

### 2. Software Installation
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Clone this repository:
   ```bash
   git clone https://github.com/Customize5773/Arduino-School-Project/Analog-Digital-LED-Chaser.git
   ```
3. Open `arduino_code/LED_Chaser_Game.ino`
4. Select correct board (Arduino Uno) and port
5. Click "Upload"

### 3. Calibration
1. Adjust potentiometer to set game speed
2. Open Serial Monitor (Ctrl+Shift+M) to view game messages
3. Verify RGB LED shows target color

## How to Play
1. The RGB LED displays a target color (blue, red, or yellow)
2. LEDs chase in sequence at speed set by potentiometer
3. Press button when the lit LED matches target color
4. Score increases for correct matches, decreases for wrong ones
5. Win at +5 points, lose at -5 points

**Game Rules**:
- Correct match: +1 point
- Wrong match: -1 point
- Win condition: Reach 5 points
- Game resets automatically after win/lose

## Customization

### Code Modifications
Edit `LED_Chaser_Game.ino` to:
```cpp
// Change difficulty thresholds
const int WIN_SCORE = 5;     // Modify win threshold
const int LOSE_SCORE = -5;   // Modify lose threshold

// Adjust LED timing (in milliseconds)
const int RESET_DELAY = 1500;
```

### Hardware Upgrades
1. **Add Sound**:
   ```cpp
   // In setup():
   pinMode(BUZZER_PIN, OUTPUT);
   
   // When correct:
   tone(BUZZER_PIN, 1000, 200);
   ```
2. **Display Scores**:
   - Connect 7-segment display or LCD
3. **Wireless Control**:
   - Add Bluetooth module for phone speed adjustment

## Acknowledgments
- Original concept & inspiration: [Instructables Project](https://www.instructables.com/Arduino-LED-Chaser-Game-Use-of-555-Timer-4017-Coun/)
