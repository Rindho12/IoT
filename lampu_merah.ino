// Pin LED
int pinHijau = 25;
int pinKuning = 26;
int pinMerah = 27;

// Status Lampu
int hijau = 1;
int kuning = 0;
int merah = 0;

// Waktu LED
unsigned long lamaHijau = 3000;
unsigned long lamaKuning = 800;
unsigned long lamaMerah = 6000;

unsigned long timeUp;
unsigned long upLed = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinHijau, OUTPUT);
  pinMode(pinKuning, OUTPUT);
  pinMode(pinMerah, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  timeUp = millis();
  if(kuning == 1) {
    if(upLed == 0) {
      upLed = timeUp;
      digitalWrite(pinKuning, HIGH);
      digitalWrite(pinHijau, LOW);
      digitalWrite(pinMerah, LOW);
    } else {
      if(timeUp-upLed == lamaKuning) {
        if(hijau == 1) {
          hijau = 0;
          merah = 1;
        } else {
          hijau = 1;
          merah = 0;
        }
        upLed = 0;
        kuning = 0;
      }
    }
    
  } else if(hijau == 1){
    if(upLed == 0) {
      upLed = timeUp;
      digitalWrite(pinHijau, HIGH);
      digitalWrite(pinKuning, LOW);
      digitalWrite(pinMerah, LOW);
    } else {
      if(timeUp-upLed == lamaHijau) {
        upLed = 0;
        hijau = 1;
        kuning = 1;
        merah = 0;
      }
    }
  } else {
    if(upLed == 0) {
      upLed = timeUp;
      digitalWrite(pinHijau, LOW);
      digitalWrite(pinKuning, LOW);
      digitalWrite(pinMerah, HIGH);
    } else {
      if(timeUp-upLed == lamaMerah) {
        upLed = 0;
        hijau = 0;
        kuning = 1;
        merah = 1;
      }
    }
  }
}
