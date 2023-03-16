#include <WiFiClient.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "HC_DHTSensors.h"
#include "HC_http.h"

void HC_httpClass::init(const char * serverAddress, int p) {
    server = serverAddress;
    port = p;
}


JsonObject HC_httpClass::getTmpHumPayload(JsonObject root) {

    JsonObject temperatureObject = root.createNestedObject("temperature");

    temperatureObject["value"] = HC_DHTSensors.hc_temperature ;
    temperatureObject["unit"] = "°C";

    JsonObject humidityObject = root.createNestedObject("humidity");

    humidityObject["value"] =  HC_DHTSensors.hc_humidity;
    humidityObject["unit"] = "%";

    return root;
}

void HC_httpClass::postTmpHumData(){
    String contentType = "application/json";
    WiFiClient client;

    Serial.print("server: ");
    Serial.println(server);
    Serial.print("port: ");
    Serial.println(port);

    HttpClient http = HttpClient(client, server, port);

    String path = "/esp/data";
    DynamicJsonDocument doc(1024);
    JsonObject payload = getTmpHumPayload(doc.to<JsonObject>());

    String payload_string;
    serializeJson( payload, payload_string);

    Serial.print("payload_string: ");
    Serial.println(payload_string);

    http.post(path, contentType, payload_string);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
}

HC_httpClass HC_http;