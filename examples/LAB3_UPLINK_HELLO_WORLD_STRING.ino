/*
 * EX2 UPLINK HELLO WORLD STRING
 */
#include <Arduino.h>
#include <SensorLink.h>

// create new lora variable
SensorLink lora;

void setup()
{

    Serial.begin(115200);  // Serial monitor
    Serial2.begin(115200); // Lorawan module serial

    // reboot LoRaWAN module
    lora.set_reboot();
    delay(60000);

    // connect to LoRaWAN
    lora.join();
}

void loop()
{

    // send "hello world" uplink on port 11 in String format
    lora.send(11, "hello world");
    delay(60000);
}
