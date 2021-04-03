

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);

}



void loop() {
  // pu
  int suti;
  if(Serial2.available()){
    suti = Serial2.read();
    //suti = (suti << 8) || Serial2.read();
    Serial.println(suti);
  }
}
