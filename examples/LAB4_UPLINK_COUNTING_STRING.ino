#include <Arduino.h>
#include <SensorLink.h>

//  ສ້າງຕົວປ່ຽນຊື່ lora
SensorLink lora;

int count = 0;
long period = 1200000;
unsigned long time_now = 0;

void setup()
{
    Serial.begin(115200);  // Serial monitor
    Serial2.begin(115200); // Lorawan module serial

    // ຣີບູດໂມດູນ LoRaWAN
    lora.set_reboot();
    delay(30000);

    // ເຊື່ອມຕໍ່ເຂົ້າກັບເຄື່ອຂ່າ LoRaWAN
    lora.join();
}

void re_join()
{
    while (lora.get_njs() == "JOINED")
    {
        lora.join();
        Serial.println(" DEVICE IS ATTEMPTING TO JOINN NETWORK");
        delay(10000);
    }
}

void loop()
{
    if (millis() >= time_now + period)
    {
        String payload = String(count);
        if (lora.get_njs() == "JOINED")
        {
            lora.send(11, payload);
        }
        else
        {
            re_join();
        }

        count++;
        time_now += period;
    }
}
