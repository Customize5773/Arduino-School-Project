# HabiBot V1.0 Bill of Materials

## Core Components
| Part | Qty | Specs | Example Source |
|------|-----|-------|----------------|
| Arduino Nano | 1 | ATmega328P | [Amazon](https://a.co/d/h3j5KkX) |
| SG90 Micro Servo | 2 | 9g torque | [Adafruit](https://www.adafruit.com/product/169) |
| HC-SR04 Ultrasonic Sensor | 1 | 2-400cm range | [SparkFun](https://www.sparkfun.com/products/15569) |
| Mini Breadboard | 1 | 170-point | [Amazon](https://a.co/d/0fZzQ6T) |
| Jumper Wires | 10 | M-M 20cm | [Amazon](https://a.co/d/4W4j0bF) |
| Ball Caster | 1 | 15mm | [Pololu](https://www.pololu.com/product/1219) |

## LiPo Power Upgrade
| Part | Qty | Specs | Notes | Example Source |
|------|-----|-------|-------|----------------|
| 2S LiPo Battery | 1 | 7.4V 1000-2000mAh | XT30 connector | [HobbyKing](https://hobbyking.com/en_us/turnigy-1000mah-2s-20c-lipo-pack.html) |
| XT30 Connector | 1 pair | Male/Female | Battery interface | [Amazon](https://a.co/d/8UxGvQn) |
| 10kΩ Resistors | 2 | 1/4W | Voltage divider | [Amazon](https://a.co/d/7VdGQJm) |
| LiPo Charger | 1 | 2S balance | Required for charging | [HobbyKing](https://hobbyking.com/en_us/imax-b6ac-v2-professional-balance-charger-discharger.html) |
| Buck Converter (Optional) | 1 | 5V 3A | For stable 5V output | [Pololu](https://www.pololu.com/product/2850) |

## Printed Parts
| Part | File | Material | Print Time |
|------|------|----------|-----------|
| Main Chassis | `chassis.stl` | PLA/PETG | ~4 hours |
| Sensor Mount | `sensor_mount.stl` | PLA | ~1 hour |
| Battery Holder | `battery_tray.stl` | TPU (flexible) | ~2 hours |

## Total Estimated Cost
| Category | Cost Range |
|----------|-----------|
| Core Components | $25-35 |
| LiPo Upgrade | $30-50 |
| 3D Printing | $5-10 (filament) |
| **Total** | **$60-95** |

## Recommended Suppliers
1. **Electronics**: 
   - [Adafruit](https://www.adafruit.com/) 
   - [SparkFun](https://www.sparkfun.com/)
   - [Pololu](https://www.pololu.com/)
2. **Batteries/RC**:
   - [HobbyKing](https://hobbyking.com/)
   - [GetFPV](https://www.getfpv.com/)
3. **Consumables**:
   - [Amazon](https://www.amazon.com/) (resistors, wires)
   - [PCBWay](https://www.pcbway.com/) (custom PCB option)

> **Safety Note**: Always use LiPo safe bags during charging/storage
