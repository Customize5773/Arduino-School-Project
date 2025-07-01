import serial
import csv
from datetime import datetime
import time

# Configuration
SERIAL_PORT = 'COM3'  # Change to your Arduino's port (Windows: COMX, Linux/Mac: /dev/ttyXXXX)
BAUD_RATE = 9600
LOG_FILE = "motion_log.csv"
LOG_INTERVAL = 1.0  # Seconds between log writes

def main():
    # Initialize serial connection
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {ser.name}")
    
    # Initialize CSV file
    with open(LOG_FILE, 'a', newline='') as f:
        writer = csv.writer(f)
        # Write header if file is empty
        if f.tell() == 0:
            writer.writerow(['timestamp', 'event', 'sensor_state', 'alarm_state'])
            print("Created new log file with header")
    
    print("Logging started. Press Ctrl+C to stop...")
    last_write = time.time()
    buffer = []
    
    try:
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                if "|" in line:  # Filter valid log lines
                    timestamp, event = line.split(" | ")
                    buffer.append([
                        datetime.now().isoformat(),
                        event.strip(),
                        "MOTION" if "ACTIVATED" in event else "STILL",
                        "ON" if "ACTIVATED" in event else "OFF"
                    ])
            
            # Write buffer at intervals
            if time.time() - last_write > LOG_INTERVAL and buffer:
                with open(LOG_FILE, 'a', newline='') as f:
                    writer = csv.writer(f)
                    writer.writerows(buffer)
                print(f"Logged {len(buffer)} events")
                buffer = []
                last_write = time.time()
                
            time.sleep(0.1)
            
    except KeyboardInterrupt:
        print("\nLogging stopped")
    finally:
        ser.close()

if __name__ == "__main__":
    main()
