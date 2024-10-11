#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "****** ********";         // Replace with your network SSID
const char *password = "**** *****"; // Replace with your network password

WiFiUDP udp;
unsigned int localUdpPort = 12345;      // Local port to listen on
char incomingPacket[255];               // Buffer for incoming packets
const int switchPin = 2;                   // GPIO2 for the LED
bool switchState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, OUTPUT);
  digitalWrite(switchPin, switchState);

  // Connect to Wi-Fi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  // Start UDP
  udp.begin(localUdpPort);
  Serial.printf("Now listening on IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0; // Null-terminate the string
    }
    Serial.printf("Received packet: %s\n", incomingPacket);
    
    if (strcmp(incomingPacket, "toggle") == 0) {
      switchState = !switchState;
      digitalWrite(switchPin, switchState);
    }
    else if (strcmp(incomingPacket, "on") == 0) {
      switchState = HIGH;
      digitalWrite(switchPin, switchState);
    }
    else if (strcmp(incomingPacket, "off") == 0) {
      switchState = LOW;
      digitalWrite(switchPin, switchState);
    }
    else {
      Serial.println("Invalid command");
    }
  }
}
