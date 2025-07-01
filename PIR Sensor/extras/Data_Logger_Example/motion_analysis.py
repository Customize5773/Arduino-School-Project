import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime
import matplotlib.dates as mdates

def analyze_motion_data(log_file):
    """Analyze motion sensor data and generate visualizations"""
    # Load and preprocess data
    df = pd.read_csv(log_file)
    df['timestamp'] = pd.to_datetime(df['timestamp'])
    df['alarm_state'] = df['alarm_state'].map({'ON': 1, 'OFF': 0})
    df['sensor_state'] = df['sensor_state'].map({'MOTION': 1, 'STILL': 0})
    
    # Filter to only include alarm events
    alarm_df = df[df['event'].str.contains('ALARM', case=False)].copy()
    
    # Create figure with subplots
    plt.figure(figsize=(14, 10))
    plt.suptitle('PIR Sensor Motion Analysis', fontsize=16)
    
    # Plot 1: Motion Detection Timeline
    ax1 = plt.subplot(3, 1, 1)
    plt.plot(df['timestamp'], df['sensor_state'], 'g-', label='Motion Detection')
    plt.plot(df['timestamp'], df['alarm_state'], 'r-', label='Alarm State')
    plt.title('Motion and Alarm Timeline')
    plt.ylabel('State')
    plt.legend()
    
    # Highlight alarm periods
    for _, row in alarm_df.iterrows():
        if 'ACTIVATED' in row['event']:
            plt.axvspan(row['timestamp'], row['timestamp'] + pd.Timedelta(minutes=5), 
                         alpha=0.2, color='red')
    
    # Plot 2: Alarm Event Duration Analysis
    ax2 = plt.subplot(3, 1, 2, sharex=ax1)
    alarm_events = alarm_df.groupby(alarm_df['timestamp'].dt.date)['event'].count()
    alarm_events.plot(kind='bar', color='coral')
    plt.title('Daily Alarm Events')
    plt.xlabel('Date')
    plt.ylabel('Number of Alarms')
    
    # Plot 3: Motion Detection Heatmap
    ax3 = plt.subplot(3, 1, 3)
    df['hour'] = df['timestamp'].dt.hour
    hourly_motion = df.groupby('hour')['sensor_state'].mean()
    plt.bar(hourly_motion.index, hourly_motion.values, color='teal')
    plt.title('Hourly Motion Detection Patterns')
    plt.xlabel('Hour of Day')
    plt.ylabel('Motion Probability')
    plt.xticks(range(0, 24))
    plt.grid(axis='y', alpha=0.3)
    
    # Format date axis
    ax1.xaxis.set_major_formatter(mdates.DateFormatter('%m/%d %H:%M'))
    plt.gcf().autofmt_xdate()
    
    # Save and show
    plt.tight_layout(rect=[0, 0, 1, 0.96])
    plt.savefig('motion_analysis.png', dpi=120)
    plt.show()
    
    # Print statistics
    total_alarms = len(alarm_df[alarm_df['event'].str.contains('ACTIVATED')])
    motion_hours = hourly_motion.idxmax()
    print(f"\nAnalysis Summary:")
    print(f"- Total alarms triggered: {total_alarms}")
    print(f"- Peak motion hours: {motion_hours}:00 - {motion_hours+1}:00")
    print(f"- Average motion probability: {df['sensor_state'].mean():.2%}")
    print(f"Visualization saved to motion_analysis.png")

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description='Analyze PIR sensor data')
    parser.add_argument('log_file', help='Path to CSV log file')
    args = parser.parse_args()
    
    analyze_motion_data(args.log_file)
