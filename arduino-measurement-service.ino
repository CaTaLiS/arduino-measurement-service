#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 0, 50);
IPAddress subnet(255, 255, 255, 128);
IPAddress dnServer(87, 204, 204, 204);
IPAddress gateway(10, 0, 0, 1);

unsigned int localUdpPort = 90;

EthernetUDP udp;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

void initSerial() {
  Serial.begin(9600);
  while(!Serial) {}
}

void initNetworkLogin() {
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  delay(5000);
  udp.begin(localUdpPort);
  Serial.print("Arduino IP = ");
  Serial.println(Ethernet.localIP());
  Serial.println("Network setup done!");
}

void setup() {
  initSerial();
  initNetworkLogin();
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("from ");
    IPAddress remote = udp.remoteIP();
    for(int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(udp.remotePort());

    udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
  }
}
