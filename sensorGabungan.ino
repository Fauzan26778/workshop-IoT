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

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
   Serial.print("Connecting Wifi: ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

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
  bot.sendMessage(CHAT_ID, "MONITORING TANAMAN SMKN7 BALEENDAH");
  //delay(2000);
  kirimPesanTelegram(h,t,M);
}

void kirimPesanTelegram(float h, float t, float M){
  String pesan = "Suhu saat in: " + String(t, 2) + "C\n" +
  "Humiditas udara saat ini: " + String(h, 2) + "%\n" + 
  "Tingkat kelembapan tanah saat ini: " + (M) + "%\n";

  if(bot.sendMessage(CHAT_ID, pesan, "Markdon")){
    Serial.println("Pesan berhasil terkirim");
  } else {
    Serial.println("Gagal terkirim");
  }
  delay(1000);
}




