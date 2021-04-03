#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

String MACadd = "8C:AA:B5:85:F3:6A";
uint8_t address[6] = {0x8C, 0xAA, 0xB5, 0x85, 0xF3, 0x6A};
bool connected;
char *pin = "1234";

void setup() {
  // put your setup code here, to run once:
  SerialBT.begin("ESP32Master", true);
  //SerialBT.setPin(pin);
  pinMode(5, INPUT_PULLUP);
  connected = SerialBT.connect(address);

  if(connected) {
    
  } else {
    while(!SerialBT.connected(10000)) {
      
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  SerialBT.write(digitalRead(5));
  
  
  delay(10);
}
