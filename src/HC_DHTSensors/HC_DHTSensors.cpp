#include "HC_DHTSensors.h"
#include "HC_Icons.h"

#ifdef ESP32
#include "heltec.h"

float hc_temperature = 0;
float hc_humidity = 0;

void HC_DHTSensorsClass::displayTempHumidityOnOled(){
    // delay(getMinimumSamplingPeriod());

    String temperatureDisplay ="" + (String) getTemperature() + "°C";
    String humidityDisplay = "" + (String) getHumidity() + " %";

    Heltec.display->clear();

    Heltec.display->setFont(ArialMT_Plain_24);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);

    Heltec.display->drawIco16x16(10,6, HC_Icons::temperature_icon16x16);
    Heltec.display->drawString(74, 0, temperatureDisplay);

    Heltec.display->drawIco16x16(10,38, HC_Icons::humidity2_icon16x16);
    Heltec.display->drawString(74, 32, humidityDisplay);

    Heltec.display->display();
};
#elif defined(ESP8266)

void HC_DHTSensorsClass::displayTempHumidity(){
    delay(getMinimumSamplingPeriod());

    String temperatureDisplay ="Temperature: " + (String) getTemperature() + "°C";
    String humidityDisplay = "Humidity: " + (String) getHumidity() + " %";


    Serial.println(temperatureDisplay);
    Serial.println(humidityDisplay);
};
#endif


void HC_DHTSensorsClass::updateHcValues() {
    hc_temperature = getTemperature();
    hc_humidity = getHumidity();
}

HC_DHTSensorsClass HC_DHTSensors;