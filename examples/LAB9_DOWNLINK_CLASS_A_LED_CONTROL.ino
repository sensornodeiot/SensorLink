#include "SensorLink.h"
SensorLink lora;

unsigned long last1;
#define LEDPIN 12 // sensor node

void setup()
{

    Serial.begin(9600);
    Serial2.begin(9600);

    pinMode(LEDPIN, OUTPUT);

    lora.join();
}

void loop()
{

    if (millis() - last1 >= 10000)
    {
        last1 = millis();

        lora.lpsend(22, "0000");

        String payload = lora.payload("A");

        if (payload == "0101")
        {
            digitalWrite(LEDPIN, 1);
            Serial.println("Turn on LED");
        }
        else if (payload == "0100")
        {
            digitalWrite(LEDPIN, 0);
            Serial.println("Turn off LED");
        }
        else
        {
            Serial.print("Unknow : ");
            Serial.println(payload);
            payload = "";
        }

        if (payload != "")
            Serial.println("==> Downlink = " + lora.dport + ":" + lora.dpayload);
    }
}
