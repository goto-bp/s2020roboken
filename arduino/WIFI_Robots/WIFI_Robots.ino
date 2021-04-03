#include<WiFi.h>
#include<WiFiUDP.h>

#define OUTPIN 17

const char *ssid = "ESP32-SWITCH"; //SSID
const char *pass = "test1234"; //パスワード
const IPAddress ip(192, 168, 0, 9); //サーバーのIPアドレス
const IPAddress subnet(255, 255, 255, 0); //サブネットマスク
bool flag = true;
int timer = 0;
int val;

WiFiClient client;
WiFiUDP udp;

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPIN, OUTPUT);
  Serial.begin(115200);

  WiFi.softAP(ssid, pass);
  delay(100);
  WiFi.softAPConfig(ip, ip, subnet);

  IPAddress myIP = WiFi.softAPIP();
  
  Serial.print("IP address : ");
  Serial.println(myIP);

  udp.begin(10000);
}



void loop() {
  // put your main code here, to run repeatedly:
  
  
  
  if (udp.parsePacket()) {
    val = udp.read(); 
    Serial.println(val);
    timer = 0;
  }

  if(timer > 5000) {
    val = -1;
  }
  
  if(val == 0) digitalWrite(OUTPIN, LOW);
  else digitalWrite(OUTPIN, HIGH);

  timer++;
}
