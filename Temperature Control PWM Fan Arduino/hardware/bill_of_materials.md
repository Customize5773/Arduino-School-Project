# Bill of Materials - Temperature Controlled PWM Fan System

| **Component**               | **Quantity** | **Specifications**                           | **Estimated Cost** | **Purpose**                                  |
|-----------------------------|--------------|----------------------------------------------|--------------------|---------------------------------------------|
| **Main Controller**         |              |                                              |                    |                                             |
| Wemos D1 Mini               | 1            | ESP8266, 4MB Flash                           | $3-5               | Main microcontroller                       |
| **Cooling Components**      |              |                                              |                    |                                             |
| 120mm 4-Pin PWM Fan         | 1+           | 12V DC, e.g., Arctic P12 PWM PST             | $8-15              | Primary cooling device                     |
| **Temperature Sensing**     |              |                                              |                    |                                             |
| DS18B20 Sensor              | 1+           | Waterproof version (TO-92 package)           | $1-3               | Temperature measurement                    |
| 4.7kΩ Resistor              | 1 per sensor | 1/4W Carbon Film                             | $0.10              | DS18B20 pull-up resistor                   |
| **Power Management**        |              |                                              |                    |                                             |
| IRLB8721 MOSFET             | 1 per fan    | Vds=30V, Id=62A, Logic-Level Gate            | $0.50-1            | PWM fan control                            |
| 100-220Ω Resistor           | 1 per fan    | 1/4W Carbon Film                             | $0.10              | MOSFET gate protection                     |
| 12V Power Supply            | 1            | 2A+ (depends on fan count)                   | $5-15              | System power source                        |
| DC Buck Converter           | 1            | 12V-to-5V, 1A+ (e.g., LM2596)                | $1-3               | Wemos/OLED power supply                    |
| **User Interface**          |              |                                              |                    |                                             |
| OLED Display                | 1            | 0.96" I2C, 128x64, SSD1306 controller       | $3-6               | Temperature/speed visualization            |
| **Optional Components**     |              |                                              |                    |                                             |
| Fan Tachometer Cable        | 1 per fan    | 3-pin to Dupont (if not included with fan)   | $0.50              | RPM monitoring                             |
| 100nF Capacitor             | 1 per fan    | Ceramic, 50V                                 | $0.20              | Fan power stabilization                    |
| 1N4007 Diode                | 1 per fan    | 1A, 1000V                                    | $0.10              | Back-EMF protection                        |
| Tactile Buttons             | 2-3          | 6x6mm SMD or through-hole                    | $0.20 each         | Manual temperature adjustment              |
| 10kΩ Resistors              | 2-3          | 1/4W Carbon Film                             | $0.10              | Button pull-down resistors                 |
| **Enclosure & Wiring**      |              |                                              |                    |                                             |
| Project Enclosure           | 1            | 100x80x50mm+ (size depends on components)    | $2-5               | System protection                          |
| JST Connectors              | As needed    | 2-4 pin                                      | $0.30 each         | Secure wiring connections                  |
| Dupont Wires                | 1 set        | Male-to-Female, 20cm                         | $1-2               | Breadboard/prototype connections           |
| PCB Prototype Board         | 1            | Perfboard or custom PCB                      | $1-5               | Permanent mounting                         |

## Total Estimated Cost: $25-50 (depending on component quality and sourcing)

## Recommended Suppliers:
1. **Main Components**:
   - [DigiKey](https://www.digikey.com/) for MOSFETs and sensors
   - [Adafruit](https://adafruit.com/) for OLED displays and Wemos boards
   - [Amazon](https://amazon.com/) for fans and power supplies

2. **Budget Options**:
   - [AliExpress](https://aliexpress.com/) for all components (longer shipping)
   - [eBay](https://ebay.com/) for surplus electronics

## Critical Notes:
1. **Fan Requirements**: Must be true 4-pin PWM (not voltage-controlled DC fan)
2. **Power Calculations**:
   - Typical 120mm fan: 0.2A @ 12V = 2.4W
   - Add 20-50% overhead for startup surge
   - Example for 3 fans: 3 × 0.3A = 0.9A → Use 12V/2A PSU
3. **MOSFET Alternatives**:
   - IRLZ44N (slightly higher gate charge)
   - STP55NF06L (comparable specs)
4. **Sourcing Tips**:
   - Buy extra DS18B20 sensors (common failure point)
   - Choose fans with PWM-stop feature (0% PWM = fan off)
   - Waterproof DS18B20 recommended for humidity resistance

## Safety Considerations:
1. Always include gate resistor for MOSFET (prevents oscillation)
2. Add fuse on 12V input (1-2A fast-blow recommended)
3. Include reverse polarity protection for power input
4. Maintain proper clearance between 12V and 3.3V circuits
