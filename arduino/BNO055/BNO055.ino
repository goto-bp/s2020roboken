

#include <Wire.h>
#define BNO055 0x28



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (1) {
    
    Wire.begin();
    delay(30);

    byte value;
    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
    Wire.requestFrom(0x28, (byte)1);
    value = Wire.read();
    if (value != 0xA0) {
      
      delay(1000);
      Wire.beginTransmission(0x28);
      Wire.write((uint8_t)0x00);
      Wire.endTransmission();
      Wire.requestFrom(0x28, (byte)1);
      value = Wire.read();
      if (value != 0xA0) {
        continue;
      }
    }

    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x3D);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();

    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x3F);
    Wire.write((uint8_t)0x20);
    Wire.endTransmission();
    delay(30);

    value = 0;
    while (value != 0xA0) {
      Wire.beginTransmission(0x28);
      Wire.write((uint8_t)0x00);
      Wire.endTransmission();
      Wire.requestFrom(0x28, (byte)1);
      value = Wire.read();
      delay(10);
    }
    delay(50);

    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x3E);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
    delay(10);

    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x07);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();

    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x3F);
    Wire.write((uint8_t)0x0);
    Wire.endTransmission();
    delay(10);

    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x3D);
    Wire.write((uint8_t)0x0C);
    Wire.endTransmission();
    delay(20);

    break;

  }

  /* Initialise the sensor */
  

  delay(1000);


  

  Wire.beginTransmission(0x28);
  Wire.write((uint8_t)0x3D);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
  delay(25);
  
  Wire.beginTransmission(0x28);
  Wire.write((uint8_t)0x07);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
  if (1) {
    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x3F);
    Wire.write((uint8_t)0x80);
    Wire.endTransmission();
  } else {
    Wire.beginTransmission(0x28);
    Wire.write((uint8_t)0x3F);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
  }
  delay(10);
  /* Set the requested operating mode (see section 3.3) */
  Wire.beginTransmission(0x28);
  Wire.write((uint8_t)0x3D);
  Wire.write((uint8_t)0x0C);
  Wire.endTransmission();
  delay(25);
  delay(20);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");




}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buffer[6];
  memset(buffer, 0, 6);

  Wire.beginTransmission(0x28);
  Wire.write((uint8_t)0x1A);
  Wire.endTransmission();
  Wire.requestFrom(0x28, 6);

  for (int i = 0; i < 6; i++) {
    buffer[i] = Wire.read();
    //Serial.println(buffer[i]);
  }

  int16_t axRaw, ayRaw, azRaw;

  axRaw = ((int16_t)buffer[0]) | (((int16_t)buffer[1]) << 8);
  ayRaw = ((int16_t)buffer[2]) | (((int16_t)buffer[3]) << 8);
  azRaw = ((int16_t)buffer[4]) | (((int16_t)buffer[5]) << 8);

  double acc_x = ((double)axRaw) / 16.0;
  double acc_y = ((double)ayRaw) / 16.0;
  double acc_z = ((double)azRaw) / 16.0;

  Serial.print(acc_x);  Serial.print(",");
  Serial.print(acc_y);  Serial.print(",");
  Serial.println(acc_z);



  delay(100);
}
