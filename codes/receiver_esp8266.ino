#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "NOTHING_SECURED";
const char* password = "39d3:25G";

WiFiUDP udp;
const unsigned int localPort = 4210;

char incomingPacket[255];
float distanceCM = 0.0;

#define AVERAGE_COUNT 5
float readings[AVERAGE_COUNT];
int currentIndex = 0;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  udp.begin(localPort);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Waiting for data...");
  display.display();
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = '\0';

    float newReading = atof(incomingPacket);
    readings[currentIndex] = newReading;
    currentIndex = (currentIndex + 1) % AVERAGE_COUNT;

    float sum = 0.0;
    for (int i = 0; i < AVERAGE_COUNT; i++) sum += readings[i];
    distanceCM = sum / AVERAGE_COUNT;

    float maxDistance = 116.8;
    float waterHeight = maxDistance - distanceCM;
    float percentFull = (waterHeight / maxDistance) * 100.0;
    float liters = (percentFull / 100.0) * 1000.0;

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("Tank: ");
    display.print((int)liters);
    display.println("L");

    display.setTextSize(3);
    display.setCursor(0, 40);
    display.print((int)percentFull);
    display.println("%");

    display.display();
  }
}
