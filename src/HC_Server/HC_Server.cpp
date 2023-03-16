#include "ESPAsyncWebServer.h"
#include "HC_DHTSensors.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include <math.h>

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

namespace HC_Server {
  AsyncWebServer server(80);
  AsyncWebServer discoveryServer(1707);

  AsyncEventSource events("/events");

  JsonObject getTmpHumPayload(JsonObject root) {

    JsonObject temperatureObject = root.createNestedObject("temperature");

    temperatureObject["value"] = HC_DHTSensors.hc_temperature ;
    temperatureObject["unit"] = "°C";

    JsonObject humidityObject = root.createNestedObject("humidity");

    humidityObject["value"] =  HC_DHTSensors.hc_humidity;
    humidityObject["unit"] = "%";

    return root;
  }

  void init() {
    server.on("/8d777f385d3dfec8815d20f7496026dc", HTTP_GET, [](AsyncWebServerRequest * request) {
      Serial.printf("handle request");
      AsyncJsonResponse * response = new AsyncJsonResponse();
      response->addHeader("Server","ESP Async Web Server");

      getTmpHumPayload(response->getRoot());

      response->setLength();
      request->send(response);
    });

  // events.onConnect([](AsyncEventSourceClient *client){
  //     if(client->lastId()){
  //       // Serial.printf("Client reconnected! Last message ID that it gat is: %u\n", client->lastId());
  //     }

  //     client->send(WiFi.getHostname(),NULL,millis(),1000);
  //   });

    server.addHandler(&events);

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

    server.begin();
  }

  void sendEvent() {
    DynamicJsonDocument doc(1024);

    JsonObject payload = getTmpHumPayload(doc.to<JsonObject>());

    String payload_string;
    serializeJson( payload, payload_string);

    events.send(payload_string.c_str(),"message",millis());
  }

  void discoveryService() {

    discoveryServer.on("/54818b05d116eadc7f67517a3a6e4b33", HTTP_GET, [](AsyncWebServerRequest * request) {

      IPAddress ip = WiFi.localIP();

      AsyncJsonResponse * response = new AsyncJsonResponse();
      response->addHeader("Server","ESP Async Web Server");

      JsonObject root = response->getRoot();
      root["ip"] = ip.toString();
      root["hostname"] = WiFi.getHostname();

      response->setLength();
      request->send(response);
    });

    discoveryServer.begin();
  }
}