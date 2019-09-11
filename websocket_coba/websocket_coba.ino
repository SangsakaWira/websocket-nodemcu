#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <SocketIoClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
}

void setup() {
    USE_SERIAL.begin(115200);

    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    WiFiMulti.addAP("MEDOKAN BARU IV NO 12", "widyastuti");

    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    webSocket.on("sensor_1", event);
    webSocket.begin("ipaddress",6500);
//    webSocket.begin("ipaddress",80,"/websocket");
    // use HTTP Basic Authorization this is optional remove if not needed
//    webSocket.setAuthorization("username", "password");
}

void loop() {
    webSocket.loop();
    webSocket.emit("iot_push", sensor);
    delay(1000);
}
