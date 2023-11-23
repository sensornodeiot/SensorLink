#include <SensorLink.h>

int LEDPIN = 2;
int SWPIN = 33;
boolean state = 0;
boolean oldState;
boolean data;

SensorLink lora;

void setup()
{

    Serial.begin(9600);
    Serial2.begin(9600);

    pinMode(LEDPIN, OUTPUT);
    pinMode(SWPIN, INPUT_PULLUP);

    lora.join();
    lora.lpsend(85, "0000");
}

void loop()
{
    data = digitalRead(SWPIN);

    if (data == 0 and oldState == 1)
    {
        delay(10);
        if (digitalRead(SWPIN) == 0)
        {
            state = !state;
            digitalWrite(LEDPIN, state);
            Serial.print("SW current state: ");
            Serial.println(state);

            lora.lpsend(88, "0" + String(state));
            Serial.print("LoRa uplink: ");
            Serial.println(state);
        }
    }

    oldState = data;
}
