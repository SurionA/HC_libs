#ifdef ESP32
#include <WiFi.h>
#include "heltec.h"

namespace HC_WiFi {

    void connect(const char* ssid, const char *passphrase, const char *hostname) {

        // WiFi.mode(WIFI_STA);
        // WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
        if(hostname) {
            WiFi.setHostname(hostname);
        }

        WiFi.begin(ssid, passphrase, channel, bssid, connect);

        Heltec.display->setFont(ArialMT_Plain_10);
        Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);

        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Heltec.display->clear();
            Heltec.display->drawString(64, 24, "Connecting to WiFi..");
            Heltec.display->display();
        }

        IPAddress ip = WiFi.localIP();

        Heltec.display->clear();
        Heltec.display->drawString(64, 12, (String) ip.toString());
        Heltec.display->drawString(64, 36, (String) WiFi.getHostname());

        Heltec.display->display();

        delay(5000);
    };

}

#elif defined(ESP8266)
#include <ESP8266WiFi.h>
namespace HC_WiFi {

    void connect(const char* ssid, const char *passphrase, const char *hostname) {
        if(hostname) {
            WiFi.setHostname(hostname);
        }

        WiFi.begin(ssid, passphrase);

        Serial.print("Connecting to WiFi..");

        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
        }

        Serial.println();

        IPAddress ip = WiFi.localIP();

        Serial.println(ip);
        Serial.println(WiFi.getHostname());

        delay(5000);
    };

}
#endif

#include "HC_WiFi.h"
