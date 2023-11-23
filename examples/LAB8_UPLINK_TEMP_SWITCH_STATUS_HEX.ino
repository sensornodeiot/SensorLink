// LoRa Modbus Temp&Humidity Sensor

#include <ModbusMaster.h>
#include <HardwareSerial.h>
#include "SensorLink.h"
#define MAX485_DE 4

int LEDPIN = 2;
int SWPIN = 33;
boolean state = 0;
boolean oldState;
boolean data;

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
    Serial.begin(9600);
    Serial2.begin(9600);

    pinMode(LEDPIN, OUTPUT);
    pinMode(SWPIN, INPUT_PULLUP);

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
            String payload = String(temp) + String(hum) + String(state);

            Serial.print("payload : ");
            Serial.println(payload);
            Serial.print("Temp: ");
            Serial.println(t[0] / 10.0);
            Serial.print("Humi: ");
            Serial.println(t[1] / 10.0);
            Serial.print("Switch: ");
            Serial.println(state);

            lora.lpsend(99, payload);
            Serial.println("--");
        }
    }

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
        }
    }
    oldState = data;
}

void preTransmission()
{
    digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
    digitalWrite(MAX485_DE, 0);
}
