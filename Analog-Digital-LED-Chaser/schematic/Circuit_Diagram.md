# Circuit Diagram Documentation

## Overall System Architecture
```mermaid
graph TD
    A[555 Timer] -->|Clock Signal| B[4017 Counter]
    B -->|Sequential Outputs| C[LED Array]
    D[Arduino] -->|Reads LED States| C
    D -->|Controls Color| E[RGB LED]
    F[Potentiometer] -->|Sets Speed| A
    G[Push Button] -->|Player Input| D
    H[5V Power] --> A & B & D & E & F
    I[Ground] --> A & B & D & E & F & G
```

## Detailed Wiring Diagram

### 1. 555 Timer Circuit (Clock Generator)
```mermaid
flowchart LR
    subgraph 555_Timer[555 Timer - Astable Multivibrator]
        direction LR
        VCC555[Pin 8: VCC] --> R1[10KΩ Resistor]
        R1 --> R2[10KΩ Resistor]
        R2 --> DIS[Pin 7: Discharge]
        DIS --> POT[Potentiometer Wiper]
        POT -->|Speed Control| GND
        VCC555 --> THR[Pin 6: Threshold]
        THR --> C1[100μF Capacitor]
        C1 --> GND
        TRIG[Pin 2: Trigger] --> THR
        OUT[Pin 3: Output] -->|1KΩ Resistor| 4017_CLK[4017 Clock Input]
    end
```

### 2. 4017 Counter Circuit (LED Sequencer)
```mermaid
flowchart LR
    subgraph 4017_Counter[4017 Decade Counter]
        direction LR
        CLK[Pin 14: Clock] --> FROM_555
        RST[Pin 15: Reset] --> GND
        INH[Pin 13: Clock Inhibit] --> GND
        VCC4017[Pin 16: VCC] --> 5V
        GND4017[Pin 8: GND] --> GND
        
        Q0[Pin 3] --> LED1[Blue LED1]
        Q1[Pin 2] --> LED2[Red LED1]
        Q2[Pin 4] --> LED3[Yellow LED1]
        Q3[Pin 7] --> LED4[Blue LED2]
        Q4[Pin 10] --> LED5[Red LED2]
        Q5[Pin 1] --> LED6[Yellow LED2]
    end
    
    LED1 -->|330Ω| ARDUINO4[Arduino Pin 4]
    LED2 -->|330Ω| ARDUINO7[Arduino Pin 7]
    LED3 -->|330Ω| ARDUINO5[Arduino Pin 5]
    LED4 -->|330Ω| ARDUINO3[Arduino Pin 3]
    LED5 -->|330Ω| ARDUINO13[Arduino Pin 13]
    LED6 -->|330Ω| ARDUINO8[Arduino Pin 8]
```

### 3. RGB LED Circuit
```mermaid
flowchart LR
    subgraph RGB_LED[Common Anode RGB LED]
        direction LR
        ANODE[Common Anode] --> 5V
        R_CATHODE[Red Cathode] -->|330Ω| ARDUINO9[Arduino Pin 9]
        G_CATHODE[Green Cathode] -->|330Ω| ARDUINO10[Arduino Pin 10]
        B_CATHODE[Blue Cathode] -->|330Ω| ARDUINO11[Arduino Pin 11]
    end
```

### 4. Input Circuit
```mermaid
flowchart LR
    subgraph Button[Push Button]
        direction TB
        BUTTON_PIN1 -->|10KΩ Pull-down| GND
        BUTTON_PIN1 --> ARDUINO2[Arduino Pin 2]
        BUTTON_PIN2 --> GND
    end
```

## Connection Reference Table

| From Component | Pin/Connection | To Component | Pin/Connection | Wire Color | Notes |
|----------------|----------------|--------------|----------------|------------|-------|
| **Power Supply** | 5V | Breadboard | + Rail | Red | Main power line |
| **Power Supply** | GND | Breadboard | - Rail | Black | Common ground |
| **555 Timer** | Pin 1 (GND) | Breadboard | - Rail | Black | |
| **555 Timer** | Pin 8 (VCC) | Breadboard | + Rail | Red | |
| **555 Timer** | Pin 6 (THRES) | Potentiometer | Wiper | Yellow | Timing control |
| **555 Timer** | Pin 2 (TRIG) | Potentiometer | Wiper | Yellow | |
| **555 Timer** | Pin 7 (DISCH) | Resistor | 10KΩ | Orange | Timing resistor |
| **555 Timer** | Pin 3 (OUT) | Resistor | 1KΩ | Yellow | Clock signal |
| **4017 Counter** | Pin 16 (VCC) | Breadboard | + Rail | Red | |
| **4017 Counter** | Pin 8 (GND) | Breadboard | - Rail | Black | |
| **4017 Counter** | Pin 14 (CLK) | 555 Timer | Pin 3 via 1KΩ | Yellow | Clock input |
| **4017 Counter** | Pin 15 (RST) | Breadboard | - Rail | Black | Keep reset low |
| **4017 Counter** | Pin 13 (CLK INH) | Breadboard | - Rail | Black | Enable counting |
| **Potentiometer** | Pin 1 | Breadboard | + Rail | Red | |
| **Potentiometer** | Pin 3 | Breadboard | - Rail | Black | |
| **Arduino Uno** | 5V | Breadboard | + Rail | Red | Power to breadboard |
| **Arduino Uno** | GND | Breadboard | - Rail | Black | Common ground |
| **RGB LED** | Common Anode | Breadboard | + Rail | Red | |
| **Push Button** | Pin 1 | Arduino | Pin 2 | Green | Input signal |
| **Push Button** | Pin 2 | Breadboard | - Rail | Black | |

## Circuit Operation Flow

```mermaid
sequenceDiagram
    participant P as Potentiometer
    participant T as 555 Timer
    participant C as 4017 Counter
    participant A as Arduino
    participant L as LEDs
    participant R as RGB LED
    participant B as Button
    
    P->>T: Sets frequency (1-5Hz)
    loop Clock Cycle
        T->>C: Sends clock pulse
        C->>L: Activates next LED
        L->>A: Reports active LED
        A->>R: Displays target color
        B->>A: Player presses button
        A->>A: Checks if match
        alt Correct Match
            A->>R: Flash green
            A->>Serial: Increment score
        else Wrong Match
            A->>R: Flash red
            A->>Serial: Decrement score
        end
    end
```

## Key Circuit Concepts

1. **555 Timer Operation**:
   - Configured in astable mode
   - Frequency formula: f = 1.44 / ((R1 + 2R2) × C)
   - Components: R1 = 1KΩ, R2 = 10KΩ (pot), C = 100μF
   - Frequency range: ~0.5-5Hz (adjustable via potentiometer)

2. **4017 Counter Logic**:
   - 5-stage Johnson counter
   - Clock pulse advances output (Q0→Q1→Q2→...→Q5→Q0)
   - Outputs stay high for one full clock cycle

3. **LED Connection Philosophy**:
   - LEDs connected between 4017 outputs and Arduino inputs
   - When 4017 output high → LED lights AND Arduino detects high
   - Resistors protect both 4017 outputs and Arduino inputs

4. **RGB LED Control**:
   - Common anode configuration
   - Cathodes connected to PWM pins for color mixing
   - Current-limiting resistors (330Ω) on each color channel

5. **Button Input**:
   - Pull-down resistor configuration
   - Prevents floating input when button not pressed
   - Clean digital signal to Arduino

## Troubleshooting Tips

1. **No LED Sequence**:
   - Check 555 output with multimeter (should pulse)
   - Verify 4017 reset (Pin 15) is grounded
   - Confirm clock signal reaches 4017 Pin 14

2. **Arduino Not Detecting LEDs**:
   - Test with multimeter (should show 5V when LED lit)
   - Verify correct pin mapping in code
   - Check for damaged resistors

3. **RGB LED Issues**:
   - Confirm common anode connected to 5V
   - Test each color channel individually
   - Ensure PWM pins are configured as outputs

4. **Button Not Responding**:
   - Verify pull-down resistor connection
   - Test continuity across button pins
   - Check Arduino pin mode (INPUT in code)

> **Safety Note**: Always disconnect power when making circuit changes. Double-check polarities before applying power.

Would you like me to provide a template for the README.md that ties all these documents together?
