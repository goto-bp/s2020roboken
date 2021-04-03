const int CSn1 = 5; //5
const int CSn2 = 4;
const int CSn3 = 2;
const int CSn4 = 15;

const int CLK = 18;
const int DO = 19;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CSn1, OUTPUT);
  pinMode(CSn2, OUTPUT);
  pinMode(CSn3, OUTPUT);
  pinMode(CSn4, OUTPUT);
  
  pinMode(CLK, OUTPUT);
  pinMode(DO, INPUT);

  digitalWrite(CSn1, HIGH);
  digitalWrite(CSn2, HIGH);
  digitalWrite(CSn3, HIGH);
  digitalWrite(CSn4, HIGH);
  digitalWrite(CLK, HIGH);

}

void loop() {
  uint8_t senddata[10];
  uint16_t enc1;
  uint16_t enc2;
  uint16_t enc3;
  uint16_t enc4;

  
  if (Serial.available() > 0) {
    char test = Serial.read();

    if ( test == 't' ) {

      enc1 = getdata(1);
      delay(1);
      enc2 = getdata(2);
      delay(1);
      enc3 = getdata(3);
      delay(1);
      enc4 = getdata(4);
      delay(1);
      
      senddata[0] = 's';
      senddata[1] = (uint8_t)((enc1 & 0x0000FF00) >>  8);
      senddata[2] = (uint8_t)((enc1 & 0x000000FF) >>  0);
      senddata[3] = (uint8_t)((enc2 & 0x0000FF00) >>  8);
      senddata[4] = (uint8_t)((enc2 & 0x000000FF) >>  0);
      senddata[5] = (uint8_t)((enc3 & 0x0000FF00) >>  8);
      senddata[6] = (uint8_t)((enc3 & 0x000000FF) >>  0);
      senddata[7] = (uint8_t)((enc4 & 0x0000FF00) >>  8);
      senddata[8] = (uint8_t)((enc4 & 0x000000FF) >>  0);
      senddata[9] = senddata[1] + senddata[2] + senddata[3] + senddata[4] + senddata[5] + senddata[6] + senddata[7] + senddata[8];

      for (int k = 0; k < 10; k++) {
        Serial.write(senddata[k]);
      }

    }
  }
  delay(50);
}

int getdata(int select) {
  unsigned int getbyte = 0;
  if(select == 1)  digitalWrite(CSn1, LOW);
  else if(select == 2)  digitalWrite(CSn2, LOW);
  else if(select == 3)  digitalWrite(CSn3, LOW);
  else if(select == 4)  digitalWrite(CSn4, LOW);
  delayMicroseconds(1);
  for(int i=0;i<12;i++) {
    
    digitalWrite(CLK, LOW);
    delayMicroseconds(1);
    digitalWrite(CLK, HIGH);
    delayMicroseconds(1);

    getbyte = (getbyte << 1) | digitalRead(DO);
  }

  if(select == 1) digitalWrite(CSn1, HIGH);
  else if(select == 2)  digitalWrite(CSn2, HIGH);
  else if(select == 3)  digitalWrite(CSn3, HIGH);
  else if(select == 4)  digitalWrite(CSn4, HIGH);
  return getbyte;
}
