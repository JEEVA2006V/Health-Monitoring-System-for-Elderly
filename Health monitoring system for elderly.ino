#define BLYNK_TEMPLATE_ID "TMPL3NrfRhNEH"
#define BLYNK_TEMPLATE_NAME "7Health monitoring"
#define BLYNK_AUTH_TOKEN "s8A694W5V-t7V3_9sKk492HGNL4A3Ec3"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <Wire.h>
#include <MPU6050_light.h>

//Wi-Fi 
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

//Pin 
#define DHTPIN    15          // DHT22 DATA
#define DHTTYPE   DHT22
#define PULSE_PIN 34          // potentiometer or pulse sensor A-in

DHT dht(DHTPIN, DHTTYPE);
MPU6050 mpu(Wire);
BlynkTimer timer;

//Thresholds for alert
constexpr float TEMP_LIMIT = 38.0;  // °C
constexpr int   BPM_LOW    = 60;
constexpr int   BPM_HIGH   = 100;

//Exact Blynk Event IDs 
const char* EV_TEMP  = "health_temp";
const char* EV_BPM   = "health_bpm";
const char* EV_FALL  = "health_fall";

void sendSensorData()
{
  
  float temp = dht.readTemperature();
  int   bpm  = map(analogRead(PULSE_PIN), 0, 4095, 60, 120);  // rough BPM
  mpu.update();
  bool  fall = (abs(mpu.getAccX()) > 1.5 ||
                abs(mpu.getAccY()) > 1.5 ||
                abs(mpu.getAccZ()) < 0.5);

  //Serial Monitor 
  Serial.print("🌡 "); Serial.print(temp, 1); Serial.print(" °C  |  ");
  Serial.print("💓 "); Serial.print(bpm);     Serial.print(" BPM  |  ");
  Serial.print("🤸‍♂️ Fall: "); Serial.println(fall ? "YES" : "NO");

  //Dashboards 
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, bpm);
  Blynk.virtualWrite(V2, fall ? 1 : 0);

  //Push notifications 
  if (temp >= TEMP_LIMIT)
    Blynk.logEvent(EV_TEMP, String(temp, 1) + " °C");

  if (bpm <= BPM_LOW || bpm >= BPM_HIGH)
    Blynk.logEvent(EV_BPM, String(bpm));

  if (fall)
    Blynk.logEvent(EV_FALL, "Fall detected!");
}


void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(PULSE_PIN, INPUT);

  Wire.begin();
  mpu.begin(); delay(1000); mpu.calcOffsets();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendSensorData);   // run every 2 s
}


void loop()
{
  Blynk.run();
  timer.run();
}
