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

        // Serial.println();

        // char minuteStringBuff[50];
        // strftime(minuteStringBuff, sizeof(minuteStringBuff), "%M", &timeinfo);
        // Serial.println(atoi(minuteStringBuff) > 50);
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
        // char minuteStringBuff[50];
        // strftime(minuteStringBuff, sizeof(minuteStringBuff), "%S", &timeinfo);

        // return atoi(minuteStringBuff);
    }

     int getSencond() {
        struct tm timeinfo;
        if(!getLocalTime(&timeinfo)){
            Serial.println("Failed to obtain time");
            return 0;
        }

        return timeinfo.tm_sec;
        // char minuteStringBuff[50];
        // strftime(minuteStringBuff, sizeof(minuteStringBuff), "%S", &timeinfo);

        // return atoi(minuteStringBuff);
    }

}





// void initTime(String timezone){
//   struct tm timeinfo;

//   Serial.println("Setting up time");
//   configTime(0, 0, "pool.ntp.org");    // First connect to NTP server, with 0 TZ offset
//   if(!getLocalTime(&timeinfo)){
//     Serial.println("  Failed to obtain time");
//     return;
//   }
//   Serial.println("  Got the time from NTP");
//   // Now we can set the real timezone
//   setTimezone(timezone);
// }

// void printLocalTime(){
//   struct tm timeinfo;
//   if(!getLocalTime(&timeinfo)){
//     Serial.println("Failed to obtain time 1");
//     return;
//   }
//   Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S zone %Z %z ");
// }

// void setup(){
//     Heltec.begin(true, false, false);

//     HC_WiFi::connect((const char*) SECRETS::ssid, (const char*) SECRETS::password);
//   Serial.begin(115200);
// Serial.setDebugOutput(true);

//   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer, "1.pool.ntp.org", "2.pool.ntp.org");
//   delay(5000); //Take some time to open up the Serial Monitor
//   printLocalTime();