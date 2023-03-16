#include <Arduino.h>

namespace HC_ntp {

        void setTimezone(String timezone) {
          Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
          setenv("TZ", timezone.c_str(), 1);
          tzset();
        }

        void init(String timezone) {
             struct tm timeinfo;

            Serial.println("Setting up time");
            configTime(0, 0, "pool.ntp.org", "time.nist.gov");

            if(!getLocalTime(&timeinfo)){
                Serial.println("  Failed to obtain time");
                return;
            }

            Serial.println("  Got the time from NTP");
            setTimezone(timezone);
        }


    void printLocalTime() {
        struct tm timeinfo;
        if(!getLocalTime(&timeinfo)){
            Serial.println("Failed to obtain time");
            return;
        }

        char timeStringBuff[50];
        strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeinfo);
        Serial.println(timeStringBuff);
    }

    int getDelaySyncTime(int sleepInterval) {
         struct tm timeinfo;
        if(!getLocalTime(&timeinfo)){
            Serial.println("Failed to obtain time");
            return 0;
        }
        int baseDelay = sleepInterval * 60;
        int currentTime =  (timeinfo.tm_min * 60 +  timeinfo.tm_sec +baseDelay);

        return (baseDelay - fmod(currentTime, baseDelay));
    }

    int getMinutes() {
        struct tm timeinfo;
        if(!getLocalTime(&timeinfo)){
            Serial.println("Failed to obtain time");
            return 0;
        }

        return timeinfo.tm_min;
    }

     int getSencond() {
        struct tm timeinfo;
        if(!getLocalTime(&timeinfo)){
            Serial.println("Failed to obtain time");
            return 0;
        }

        return timeinfo.tm_sec;
    }

}