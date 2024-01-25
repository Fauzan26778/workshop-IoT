#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  Serial.print("Workshop monitoring tanaman smk2 baleendah\n");
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if(isnan(h) || isnan(t)){
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
  delay(2000);
}
