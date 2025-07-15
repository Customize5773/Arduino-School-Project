# Bill of Materials (BOM) - LED Chaser Game

This project combines analog 555 timer circuitry with Arduino digital control. Below is the complete component list:

## Core Components
| Component | Quantity | Specifications | Purpose |
|-----------|----------|----------------|---------|
| Arduino Uno | 1 | ATmega328P microcontroller | Game controller and logic processor |
| 555 Timer IC | 1 | NE555 or equivalent | Clock pulse generator for LED sequence |
| 4017 Decade Counter | 1 | CD4017 or equivalent | LED sequencer/chaser controller |
| Breadboard | 1 | 830 tie-points | Prototyping circuit |
| RGB LED | 1 | Common Anode, 5mm | Target color indicator |
| LEDs | 6 | 5mm (2 blue, 2 red, 2 yellow) | Main game chasing lights |
| Push Button | 1 | Tactile switch, 6x6mm | Player input |
| Potentiometer | 1 | 10KΩ linear | Game speed control |

## Passive Components
| Component | Quantity | Specifications | Purpose |
|-----------|----------|----------------|---------|
| Resistors | 5 | 2x 330Ω, 1x 1KΩ, 2x 10KΩ | Current limiting and timing |
| Capacitor | 1 | 100µF electrolytic, 10V | Timing capacitor for 555 |

## Wiring & Misc
| Component | Quantity | Specifications |
|-----------|----------|----------------|
| Jumper Wires | 15-20 | 22 AWG, assorted colors |
| 9V Battery + Barrel Jack | 1 | Optional power supply |
| USB Cable | 1 | Type-B for Arduino programming |

## Component Notes:
1. **LED Considerations**: 
   - Blue/Yellow LEDs require 330Ω resistors (higher forward voltage)
   - Red LEDs can use 220-330Ω (2.0-2.2V forward voltage)
   
2. **RGB LED Wiring**:
   ```plaintext
   Common Anode → 5V
   Red Cathode → Arduino Pin 9 via 330Ω
   Green Cathode → Arduino Pin 10 via 330Ω
   Blue Cathode → Arduino Pin 11 via 330Ω
