**HEALTH MONITORING SYSTEM FOR ELDERLY**

**OBJECTIVE**

Create a system that monitors pulse rate, temperature, and fall detection, and sends alerts if abnormalities are detected.

**COMPONENTS USED**

- ESP32 microcontroller  
- Pulse Sensor  
- DHT22 temperature sensor  
- MPU6050 accelerometer (for fall detection)  
- Blynk IoT App / Web Dashboard  


**WORKING**

1. The DHT22 sensor measures the body temperature, and the pulse sensor monitors heart rate.  
2. The MPU6050 detects sudden changes in motion, which may indicate a fall.  
3. All sensor data is sent in real-time to the Blynk cloud using Wi-Fi via the ESP32.  
4. Live values are shown using **gauge widgets** on:
   - Blynk mobile dashboard  
   - Blynk web dashboard  
5. **Alert conditions**:
   - Temperature > 38°C  
   - Pulse rate < 60 or > 100 bpm  
   - Fall detected via MPU6050  
6. If any of the above conditions occur, a** push notification is sent to the caregiver's mobile phone**.


**WHAT I LEARNED**

- Monitoring vital health parameters using sensors with ESP32  
- Displaying real-time health data using Blynk’s gauge widgets  
- Detecting fall motion events using the MPU6050  
- Sending automated push alerts to caregivers through IoT

**TOOLS USED**

Wokwi Simulator

Blynk IoT Platform


