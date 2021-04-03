#include <SPI.h>



const int CSn = 10; // Chip select
const int CLK = 13; // Clock signal
const int DO = 12; // Digital Output from the encoder which delivers me a 0 or 1, depending on the bar angle

unsigned int sensorWaarde = 0;

void setup(){
  Serial.begin(115200);

  pinMode(CSn, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DO, INPUT);

  digitalWrite(CLK, LOW);
  digitalWrite(CSn, HIGH);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
}

void loop() {
  unsigned int getsuti=0;

  getsuti = getdata();
  Serial.println(getsuti);
    
}

int getdata() {
  unsigned int getsuti = 0;
  digitalWrite(CSn, LOW);
    for(int i=0; i<12; i++) {
      digitalWrite(CLK, HIGH);
      delay(1);
      getsuti = (getsuti << 1) | SPI.transfer(0x01);  
      digitalWrite(CLK, LOW);
      delay(1);
    }
    digitalWrite(CSn, HIGH);
    return getsuti;
}
