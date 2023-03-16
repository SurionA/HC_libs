#include <Arduino.h>

#include "HC_ntp.h"

namespace HC_utils {
    using Callback = void (*)();

    int taskDone = 0;
    int uS_TO_S_FACTOR = 1000000;

    void deepSleepLoop(Callback callback, int sleepInterval ){
        int minutes = HC_ntp::getMinutes();

        if (fmod(minutes, sleepInterval) == 0 && taskDone ==0) {
            taskDone=1;
            callback();
        } else {
            taskDone=0;

            int sleepDelay = HC_ntp::getDelaySyncTime(sleepInterval);
            Serial.println();
            Serial.println("Estimated deep sleep for: " +  (String) sleepDelay + "s");

            ESP.deepSleep(sleepDelay * uS_TO_S_FACTOR);

        }
    }
}