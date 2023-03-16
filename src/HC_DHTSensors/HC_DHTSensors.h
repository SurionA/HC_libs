#include "DHTesp.h"

#ifndef hc_dhtsensors_h
#define hc_dhtsensors_h

class HC_DHTSensorsClass: public DHTesp {
    public:
        float hc_temperature;
        float hc_humidity;

        void updateHcValues();
        void displayTempHumidityOnOled();
        void displayTempHumidity();
};

extern HC_DHTSensorsClass HC_DHTSensors;

#endif