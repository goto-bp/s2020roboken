void setup() {
  Serial2.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  static int i = 10;
  Serial2.write(i);
  
  delay(100);
}
