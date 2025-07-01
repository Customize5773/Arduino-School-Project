# Additional Resources

## Python Serial Logger
Logs Arduino output to CSV file via serial connection.

### Requirements:
- Python 3.x
- pyserial (`pip install pyserial`)

### Usage:
1. Set correct `SERIAL_PORT` in script
2. Run: `python Python_Serial_Logger.py`
3. Data saved to `motion_log.csv`

### Sample Output:
timestamp,event,sensor_state,alarm_state
2023-07-01T12:30:45.123,ALARM ACTIVATED,MOTION,ON
2023-07-01T12:30:50.456,Alarm deactivated,STILL,OFF


## SD Card Data Logger
Logs sensor data directly to SD card.

### Hardware Requirements:
- SD card module
- Formatted SD card (FAT16/FAT32)

### Features:
- Creates timestamped log files
- Periodic status logging
- Event-based logging
- CSV format for easy analysis

### Wiring:
| SD Module | Arduino |
|-----------|---------|
| VCC       | 5V      |
| GND       | GND     |
| CS        | D4      |
| MOSI      | D11     |
| MISO      | D12     |
| SCK       | D13     |
