#include <BluetoothSerial.h>


BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32Slave"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if(SerialBT.available()){
    int val = SerialBT.read();
    Serial.println(val);
  }
  delay(5);
}
