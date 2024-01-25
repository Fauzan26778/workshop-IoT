int M,sensor_analog;
const int sensor_pin = 34;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  Serial.print("Workshop monitoring tanaman smk2 baleendah\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_analog = analogRead(sensor_pin);
  M = (100 - ((sensor_analog/4095.00) * 100));
  if(isnan(M)){
    Serial.println("Sensor tidak terbaca");
    return;
  }
  Serial.print("==monitoring tanaman==\n");
  Serial.print("Kelembapan air tahan: ");
  Serial.print(M); /*print kelembapan air*/
  Serial.print(" %");
  delay(2000);
}
