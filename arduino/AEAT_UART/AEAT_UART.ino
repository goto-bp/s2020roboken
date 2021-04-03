void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  byte getdata[10];
  uint16_t enc1;
  uint16_t enc2;
  uint16_t enc3;
  uint16_t enc4;
  uint8_t checksum = 0;
  // put your main code here, to run repeatedly:
  Serial2.write('t');
  if(Serial2.available() > 0){
    
    
    getdata[0] = Serial2.read();
    
    
    if(getdata[0] == 115){
      
      
      for(int i = 1; i < 10;i++){
        getdata[i] = Serial2.read();
        
        
      }
      
      enc1 = (uint16_t)((uint16_t)getdata[1] << 8 & 0x0000FF00) | (uint16_t)getdata[2];
      enc2 = (uint16_t)((uint16_t)getdata[3] << 8 & 0x0000FF00) | (uint16_t)getdata[4];
      enc3 = (uint16_t)((uint16_t)getdata[5] << 8 & 0x0000FF00) | (uint16_t)getdata[6];
      enc4 = (uint16_t)((uint16_t)getdata[7] << 8 & 0x0000FF00) | (uint16_t)getdata[8];
      checksum = getdata[1] + getdata[2] + getdata[3] + getdata[4] + getdata[5] + getdata[6] + getdata[7] + getdata[8];
      
      if(checksum == getdata[9]) {
        Serial.print(enc1);
        Serial.print("   ");
        Serial.print(enc2);
        Serial.print("   ");
        Serial.print(enc3);
        Serial.print("   ");
        Serial.println(enc4);
      }
    }else {
      while (Serial2.available() > 0)Serial2.read();
      
    }
    checksum = 0;
  }
  

  
}
