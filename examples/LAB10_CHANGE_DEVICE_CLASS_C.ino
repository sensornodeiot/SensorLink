#include "SensorLink.h"
SensorLink lora;

void setup()
{

    Serial.begin(9600);
    Serial2.begin(9600);

    lora.set_reboot();
    delay(5000);

    Serial.println("device:");
    Serial.println("> CLASS = " + lora.get_loraclass());

    lora.set_loraclass("C");

    Serial.println("Current device:");
    Serial.println("> CLASS = " + lora.get_loraclass());
}

void loop()
{
}
