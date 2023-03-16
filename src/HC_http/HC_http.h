#include <WiFiClient.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

#ifndef hc_http_h
#define hc_http_h

    class HC_httpClass {
        public:
            void init(const char * serverAddress, int p = 80);
            void postTmpHumData();
        protected:
            const char * server;
            int port;
            JsonObject getTmpHumPayload(JsonObject root);

    };

extern HC_httpClass HC_http;

#endif