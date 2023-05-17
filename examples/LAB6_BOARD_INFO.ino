#include <Arduino.h>
#include <SensorLink.h>

// ສ້າງຕົວປ່ຽນຊື່ lora
SensorLink lora;

void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200);
}

void loop()
{

    delay(5000);
    Serial.println("==> GET BOARD INFO.");
    Serial.println("> RAK AS918 LORA MODULE.");
    delay(1000);
    Serial.println("> DEVEUI = " + lora.get_deveui());
    delay(1000);
    Serial.println("> APPEUI = " + lora.get_appeui());
    delay(1000);
    Serial.println("> APPKEY = " + lora.get_appkey());
    delay(1000);
    Serial.println("> DADDR = " + lora.get_devaddr());
    delay(1000);
    Serial.println("> CLASS = " + lora.get_loraclass());
    delay(1000);
    Serial.println("> JOIN MODE = " + lora.get_njm());
    delay(1000);
    Serial.println("> JOIN STATUS = " + lora.get_njs());
    delay(1000);
    Serial.println("> ADR = " + lora.get_adr());
    delay(1000);
    Serial.println();
}
