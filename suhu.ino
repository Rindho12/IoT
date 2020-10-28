#include "DHT.h"

// Initialisasi DHT
#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//pin led
int pinMerah = 27;
int pinKuning = 26;
int pinHijau = 25;

//pin button
int pinButton = 33;

//status button
int dhtUp = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinMerah, OUTPUT);
  pinMode(pinKuning, OUTPUT);
  pinMode(pinHijau, OUTPUT);
  pinMode(pinButton, INPUT);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonUp = digitalRead(pinButton);

  if(buttonUp == HIGH) {
    if(dhtUp == 0) {
      dhtUp = 1;
      Serial.println("Mulai membaca suhu, tunggu 10 detik...");
      delay(10000);
    } else {
      dhtUp = 0;
      Serial.println("Menghetikan membaca suhu...");
      delay(3000);
      digitalWrite(pinHijau, LOW);
      digitalWrite(pinKuning, LOW);
      digitalWrite(pinMerah, LOW);
    }
  } else {
    if(dhtUp == 1) {
      float suhu = bacaSuhu();
      if(suhu != -999) {
        hidupkanLed(suhu);
      }
    }
  }
}

float bacaSuhu(){
  delay(3000);
  
  float suhu = dht.readTemperature();
  if(isnan(suhu)){
    Serial.println("Gagal membaca suhu...");
    return -999;
  }
  else{
    return suhu;
  }
}

void hidupkanLed(float suhu){
  //nyala 3 LED jika suhu dibawah 35 derajat celcius
  Serial.print("suhu : ");
  Serial.print(suhu);
  Serial.println("° Celcius");
  if(suhu < 35){
      digitalWrite(pinHijau, HIGH);
      digitalWrite(pinKuning, LOW);
      digitalWrite(pinMerah, LOW);
  }
  //nyala 2 LED jika suhu diatas 35 dan dibawah 50 derajat celcius
  else if(suhu <= 50){
      digitalWrite(pinHijau, HIGH);
      digitalWrite(pinKuning, HIGH);
      digitalWrite(pinMerah, LOW);
  }
  //nyala 3 LED jika suhu diatas 50 derajat celcius
  else if(suhu > 50){
      digitalWrite(pinHijau, HIGH);
      digitalWrite(pinKuning, HIGH);
      digitalWrite(pinMerah, HIGH);
  }
}
