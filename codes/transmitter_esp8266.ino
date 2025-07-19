#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "NOTHING_SECURED";
const char* password = "39d3:25G";

const IPAddress receiverIP(192, 168, 137, 242); // IP of receiver ESP
const unsigned int receiverPort = 4210;         // UDP port

WiFiUDP udp;
String distanceStr = "";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
  udp.begin(4211);  // Optional local port
}

void loop() {
  if (Serial.available()) {
    distanceStr = Serial.readStringUntil('\n');
    distanceStr.trim();

    if (distanceStr.length() > 0) {
      udp.beginPacket(receiverIP, receiverPort);
      udp.print(distanceStr);  // Send distance
      udp.endPacket();
      Serial.println("Sent: " + distanceStr);
    }
  }
}
