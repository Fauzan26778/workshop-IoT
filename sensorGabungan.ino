#include "DHT.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int M,sensor_analog;
const int sensor_pin = 34;

const char* ssid ="Jinan 2";
const char* password = "JinanGracia";
#define CHAT_ID "5393911117"
#define BOTtoken "6705741560:AAETk-tsNg4bh7zN3a_uqcXabBDgjMzY4FI"

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
   Serial.print("Connecting Wifi: ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

    while(WiFi.status() != WL_CONNECTED){
       Serial.print(".");
       delay(500);
    }

  delay(2000);
  Serial.print("Workshop monitoring tanaman smk2 baleendah\n");
  dht.begin();
}

void loop() {

  // put your main code here, to run repeatedly:
  sensor_analog = analogRead(sensor_pin);
  M = (100 - ((sensor_analog/4095.00) * 100));
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if(isnan(h) || isnan(t) || isnan(M)) {
     Serial.println("Sensor tidak terbaca");
    return;
  }
  Serial.print("==monitoring tanaman\n");
  Serial.print("Humaditas udara: ");
  Serial.print(h);
  Serial.print("%");
  Serial.print("Temperatur lingkungan: ");
  Serial.print(t);
  Serial.println(" C");
  Serial.print("Kelembapan air tahan: ");
  Serial.print(M); /*print kelembapan air*/
  Serial.print(" %");
  delay(2000);
}
