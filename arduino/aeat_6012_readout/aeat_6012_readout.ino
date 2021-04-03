// Read in 12-bits Magnetic Encoder AEAT-6012-A06
// RobinL modified by linarism and bstadlbauer
// If 'A' is written to the sensor: Returns the angle mapped such that full 12 bits are 360 degress
// If 'V' is written to the sensor: Returns the current Version ("sensor_vX")

const int CSn = 10; // Chip select
const int CLK = 13; // Clock signal
const int DO = 12; // Digital Output from the encoder which delivers me a 0 or 1, depending on the bar angle

unsigned int sensorWaarde = 0;

void setup(){
  Serial.begin(115200);

  pinMode(CSn, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DO, INPUT);

  digitalWrite(CLK, HIGH);
  digitalWrite(CSn, HIGH);
}

void loop() {
  char c = 0;
  
  
          sensorWaarde = readSensor();
          delayMicroseconds(1); //Tcs waiting for another read in
        
}

unsigned int readSensor(){
  unsigned int dataOut = 0;

  digitalWrite(CSn, LOW);
  delayMicroseconds(1); //Waiting for Tclkfe

  //Passing 12 times, from 0 to 11
  for(int x=0; x<12; x++){
    digitalWrite(CLK, LOW);
    delayMicroseconds(1); //Tclk/2
    digitalWrite(CLK, HIGH);
    delayMicroseconds(1); //Tdo valid, like Tclk/2
    dataOut = (dataOut << 1) | digitalRead(DO); //shift all the entering data to the left and past the pin state to it. 1e bit is MSB
  }

  digitalWrite(CSn, HIGH); //deselects the encoder from reading
  Serial.println(dataOut);
  return dataOut;
}
