#include "Sensorlink.h"
SensorLink lora;

void Task1(void *p)
{

    pinMode(2, OUTPUT);

    char r;
    String payload;
    while (true)
    {

        payload = lora.payload("C");

        if (payload == "0101")
        {
            digitalWrite(2, 1);
        }
        else if (payload == "0100")
        {
            digitalWrite(2, 0);
        }
        else
        {
            payload = "";
        }

        if (payload != "")
            Serial.println("==> Downlink = " + lora.dport + ":" + lora.dpayload);

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup()
{

    Serial.begin(9600);
    Serial2.begin(9600);

    lora.join();
    lora.lpsend(22, "000000");

    xTaskCreate(&Task1, "Task1", 1024, NULL, 10, NULL);
}

void loop()
{
}
