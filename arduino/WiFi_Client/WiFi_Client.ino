


#include <WiFi.h>
#include <WiFiUDP.h>

const char *ssid = "ESP32-SWITCH"; //SSID
const char *pass = "test1234"; //パスワード
static WiFiClient client;
static WiFiUDP wifiUdp;
const IPAddress ip(192, 168, 0, 9);
WiFiServer server(80);


void setup()
{
  pinMode(13, INPUT);
  Serial.begin(115200);
  delay(10);




  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);

  }
  Serial.println("");
  wifiUdp.begin(8000);
  Serial.println("接続成功");
}

int value = 0;

void loop()
{
  value = digitalRead(13);



  wifiUdp.beginPacket(ip, 10000);

  wifiUdp.write(value);
  Serial.print(value);
  Serial.println("を送信");
  wifiUdp.endPacket();


  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);

    }
    Serial.println("");
    wifiUdp.begin(8000);
    Serial.println("接続成功");
  }




  delay(10);
}
