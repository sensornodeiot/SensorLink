// LoRa Modbus Temp&Humidity Sensor

#include <ModbusMaster.h>
#include <HardwareSerial.h>
#include "SensorLink.h"
#define MAX485_DE 4

SensorLink lora;
unsigned long last1;

HardwareSerial ModbusSerial(2);
uint8_t result;

ModbusMaster node;

int t[2] = {};
char temp[5];
char hum[5];

void setup()
{
    delay(5000);
    Serial.begin(115200);
    Serial2.begin(115200);

    lora.join();
    lora.lpsend(85, "0000");

    ModbusSerial.begin(9600, SERIAL_8N1, 19, 18);

    pinMode(MAX485_DE, OUTPUT);
    digitalWrite(MAX485_DE, 0);

    node.begin(1, ModbusSerial);
    node.postTransmission(postTransmission);
    node.preTransmission(preTransmission);
}

void loop()
{

    if (millis() - last1 >= 15000)
    {
        last1 = millis();

        node.readInputRegisters(1, 2);
        delay(100);
        if (result == node.ku8MBSuccess)
        {
            t[0] = node.getResponseBuffer(0);
            t[1] = node.getResponseBuffer(1);

            sprintf(temp, "%04x", t[0]);
            sprintf(hum, "%04x", t[1]);
            String payload = String(temp) + String(hum);

            Serial.print("payload : ");
            Serial.println(payload);
            Serial.print("Temp: ");
            Serial.println(t[0] / 10.0);
            Serial.print("Humi: ");
            Serial.println(t[1] / 10.0);

            lora.lpsend(99, payload);
            Serial.println("--");
        }
    }
}

void preTransmission()
{
    digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
    digitalWrite(MAX485_DE, 0);
}
