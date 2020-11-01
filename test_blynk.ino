#define BLYNK_PRINT Serial
#define DHTPIN 33
#define DHTTYPE DHT11
#define WARNAHIJAU "#00FF00"
#define WARNAMERAH "#FF0000"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "NIockw54JdNMpVZG1hlTkxu33zr30ZaQ";
char ssid[] = "Zn";
char pass[] = "zn123zn456";

DHT dht(DHTPIN, DHTTYPE);
WidgetLED indikatorCahaya(V6);
WidgetLED indikatorSuhu(V7);
int pinCahaya = 26;
int pinSuhu = 27;
int LDR = 32;

int batasCahaya = 0;
int batasSuhu = 0;

int systemUp = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(pinSuhu, OUTPUT);
  pinMode(pinCahaya, OUTPUT);
  dht.begin();
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 100, 7), 8080);
}

void loop()
{
  Blynk.run();
  int suhu;
  int cahaya;
  if (systemUp == 1) {
    delay(3000);
    suhu = getSuhu();
    cahaya = getCahaya();
    Blynk.virtualWrite(V1, suhu);
    Blynk.virtualWrite(V3, suhu);
    Blynk.virtualWrite(V0, cahaya);
    Blynk.virtualWrite(V2, cahaya);
    nyalainLed(suhu, cahaya);
  }
}

int getSuhu() {
  int suhu;
  suhu = dht.readTemperature();
  if (isnan(suhu)) {
    return -999;
  }
  else {
    return suhu;
  }
}

int getCahaya() {
  int cahaya;
  cahaya = analogRead(LDR);
  if (isnan(cahaya)) {
    return -999;
  }
  else {
    cahaya = (0.009758 * cahaya) + 10;
    return cahaya;
  }
}

void nyalainLed(int suhu, int cahaya) {
  if (cahaya > batasCahaya) {
    indikatorCahaya.setColor(WARNAMERAH);
    digitalWrite(pinCahaya, HIGH);
  }
  else {
    indikatorCahaya.setColor(WARNAHIJAU);
    digitalWrite(pinCahaya, LOW);
  }
  
  if (suhu > batasSuhu) {
    indikatorSuhu.setColor(WARNAMERAH);
    digitalWrite(pinSuhu, HIGH);
  }
  else {
    indikatorSuhu.setColor(WARNAHIJAU);
    digitalWrite(pinSuhu, LOW);
  }
}

//TH cahaya
BLYNK_WRITE(V4)
{
  batasCahaya = param.asInt();
  batasCahaya = (param.asInt()*0.009768) + 10;
}

//TH suhu
BLYNK_WRITE(V5)
{
  batasSuhu = param.asInt();
}

BLYNK_WRITE(V8)
{
  int value = param.asInt();
  if (value == 1) {
    systemUp = 1;
    indikatorCahaya.on();
    indikatorSuhu.on();
  }
  else {
    systemUp = 0;
    digitalWrite(pinCahaya, LOW);
    digitalWrite(pinSuhu, LOW);
    indikatorCahaya.off();
    indikatorSuhu.off();
  }
}
