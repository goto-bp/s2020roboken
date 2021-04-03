#include <SPI.h>



const int CSn = 23;
const int CSn2 = 22;// Chip select
const int CLK = 18; // Clock signal
const int DO = 19; // Digital Output from the encoder which delivers me a 0 or 1, depending on the bar angle

uint16_t enc1;
uint16_t enc2;


void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  pinMode(CSn, OUTPUT);
  pinMode(CSn2, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DO, INPUT);

  digitalWrite(CLK, HIGH);
  digitalWrite(CSn, HIGH);



}

void loop() {
  unsigned int getsuti = 0;
  static int i = 0;
  char start = 's';
  uint8_t senddata[6];
  uint16_t test;
  uint8_t checksum;

  getsuti = getdata(i);
  if (i == 0) {
    enc1 = getsuti;
    i = 1;
  } else if (i == 1) {
    enc2 = getsuti;
    i = 0;
  }
  if (Serial2.available() > 0) {
    char test = Serial2.read();

    if ( test == 't' ) {
      senddata[0] = start;
      senddata[1] = (uint8_t)((enc1 & 0x0000FF00) >>  8);
      senddata[2] = (uint8_t)((enc1 & 0x000000FF) >>  0);
      senddata[3] = (uint8_t)((enc2 & 0x0000FF00) >>  8);
      senddata[4] = (uint8_t)((enc2 & 0x000000FF) >>  0);
      senddata[5] = senddata[1] + senddata[2] + senddata[3] + senddata[4];

      for (int k = 0; k < 6; k++) {
        Serial2.write(senddata[k]);
      }
      Serial.print(enc1);
      Serial.print("   ");
      Serial.println(enc2);

    }
  }



  delay(50);
}

int getdata(int select) {
  unsigned int getsuti = 0;
  if (select == 0) {
    digitalWrite(CSn, LOW);
    delayMicroseconds(1);
    for (int i = 0; i < 12; i++) {
      digitalWrite(CLK, LOW);
      delayMicroseconds(1);

      digitalWrite(CLK, HIGH);
      delayMicroseconds(1);
      getsuti = (getsuti << 1) | digitalRead(DO);

    }
    digitalWrite(CSn, HIGH);
  } else if (select == 1) {
    digitalWrite(CSn2, LOW);
    delayMicroseconds(1);
    for (int i = 0; i < 12; i++) {
      digitalWrite(CLK, LOW);
      delayMicroseconds(1);

      digitalWrite(CLK, HIGH);
      delayMicroseconds(1);
      getsuti = (getsuti << 1) | digitalRead(DO);

    }
    digitalWrite(CSn2, HIGH);
  }

  return getsuti;


}
