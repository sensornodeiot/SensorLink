#include <Arduino.h>
#include <SensorLink.h>

//  ສ້າງຕົວປ່ຽນຊື່ lora
SensorLink lora;

void setup()
{
    Serial.begin(115200);  // Serial monitor
    Serial2.begin(115200); // Lorawan module serial

    // ຣີບູດໂມດູນ LoRaWAN
    lora.set_reboot();
    delay(60000);

    // ເຊື່ອມຕໍ່ເຂົ້າກັບເຄື່ອຂ່າ LoRaWAN
    lora.join();
}

void loop()
{
    // ສົ່ງຂໍ້ຄວາມ "hello world" ແບບ String ໃຊ້ພອດສົ່ງ 11
    lora.send(11, "hello world");
    delay(60000);
}