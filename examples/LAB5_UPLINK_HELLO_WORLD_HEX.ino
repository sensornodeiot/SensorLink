#include <SensorLink.h>
SensorLink lora;

void setup()
{
    Serial.begin(115200);  // Serial monitor
    Serial2.begin(115200); // Lorawan module serial
    lora.join();
}

void loop()
{
    lora.lpsend(12, "68656c6c6f20776f726c64");
    delay(60000);
}
