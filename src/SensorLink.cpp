// ## VERSION: V.0.0 | Initial Version ##
// ## COMMIT: Fixed LoRa CLASS change, BUG CLASS-C ##
// ## ORG: Sensornode IoT Technology Sole Co., Ltd ##
// ## DEV: Mr. Tee Chuangthevy @ 2023 ##
// ## DATE: 28 APRIL 2023 ##

#include <Arduino.h>
#include <SensorLink.h>
#include <HardwareSerial.h>

SensorLink::SensorLink()
{
}

/*##########################################
//
//  DEFINE FUNCTION
//
###########################################*/

// GET
#define _ATZ "ATZ"                  // to trigger a reset on the module
#define _GET_AT "AT"                // to check that the link is working properly
#define _GET_RECV "AT+RECV"         // to access the last received data in hex format
#define _GET_APPEUI "AT+APPEUI=?"   // to access the unique application identifier
#define _GET_APPKEY "AT+APPKEY=?"   // to access the application key
#define _GET_APPSKEY "AT+APPSKEY=?" // to set the application session key
#define _GET_DEVADDR "AT+DEVADDR=?" // to access the device address
#define _GET_DEVEUI "AT+DEVEUI=?"   // to access the unique end-device ID
#define _GET_NWKSKEY "AT+NWKSKEY=?" // to get or set the network session key.
#define _GET_CFM "AT+CFM=?"         // to access the uplink payload to be confirmed or unconfirmed type.
#define _GET_CFS "AT+CFS=?"         // to access the status of the last SEND command
#define _JOIN "AT+JOIN"             // to join a LoRaWAN network
#define _GET_NJM "AT+NJM=?"         // to access the network join mode
#define _GET_NJS "AT+NJS=?"         // to access the current activation status of the device. It shows if the device joined or not in a LoRaWAN network
#define _GET_RECV "AT+RECV=?"       // to access the last received data in hex format
#define _GET_ADR "AT+ADR=?"         // to access the adaptive data rate
#define _GET_CLASS "AT+CLASS=?"     // to access the LoRaWAN class
#define _GET_DCS "AT+DCS=?"         // to access the duty cycle
#define _GET_DR "AT+DR=?"           // to access data rate settings
#define _GET_JN1DL "AT+JN1DL=?"     // to access the join delay info on RX window 1
#define _GET_JN2DL "AT+JN2DL=?"     // to access the join delay info on RX window 2
#define _GET_PNM "AT+PNM=?"         // to access the public network mode
#define _GET_RX1DL "AT+RX1DL=?"     // to access the delay of the received window 1
#define _GET_RX2DL "AT+RX2DL=?"     //  to access the delay of the received window 2
#define _GET_RX2DR "AT+RX2DR=?"     // to access the data rate of received window 2
#define _GET_RX2FQ "AT+RX2FQ=?"     // to access the frequency of the received window 2
#define _GET_TXP "AT+TXP=?"         // to access the transmit power
#define _GET_RSSI "AT+RSSI=?"       // to access the RSSI on reception
#define _GET_LBTRSSI "AT+LBTRSSI=?" // to get LoRaWAN LBT RSSI
#define _GET_SNR "AT+SNR=?"         // to access the SNR(Signal Noise Ratio) of the last received packet
#define _GET_VER "AT+VER=?"         // to access the version of the firmware

// SET
#define _SEND "AT+SEND="     // to send data on a dedicated port number
#define _LPSEND "AT+LPSEND=" // to send long packet text data

#define _SET_APPEUI "AT+APPEUI="
#define _SET_APPKEY "AT+APPKEY="
#define _SET_APPSKEY "AT+APPSKEY="
#define _SET_DEVADDR "AT+DEVADDR="
#define _SET_DEVEUI "AT+DEVEUI="
#define _SET_NWKSKEY "AT+NWKSKEY="
#define _SET_CFM "AT+CFM="
#define _SET_CFS "AT+CFS="
#define _SET_ADR "AT+ADR="
#define _SET_DCS "AT+DCS="
#define _SET_DR "AT+DR="
#define _SET_JN1DL "AT+JN1DL="
#define _SET_JN2DL "AT+JN2DL="
#define _SET_PNM "AT+PNM="
#define _SET_RX1DL "AT+RX1DL="
#define _SET_RX2DL "AT+RX2DL="
#define _SET_RX2DR "AT+RX2DR="
#define _SET_RX2FQ "AT+RX2FQ="
#define _SET_TXP "AT+TXP="
#define _SET_CLASS "AT+CLASS="

/*##########################################
//
//  Utility functions
//
###########################################*/

// To put the payload into standalone format
String SensorLink::payload(String at)
{
    dpayload = "";
    dport = "";
    String Input = check_payload(at);
    for (int i = 0; i < input.length(); i++)
    {
        if (input.substring(i, i + 1) == ":")
        {
            dport = input.substring(0, i);
            dpayload = input.substring(i + 1);
            break;
        }
    }
    return dpayload;
}

// Get AT Command, parse AT parameters
String SensorLink::atcmd_key(String at)
{
    char r[10];
    String txt = "";
    Serial2.print(at);
    delay(200);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isHexadecimalDigital(r[i]) or r[i] == ":")
        {
            txt += r[i];
        }
        i++;
    }
    return txt;
}

// To get lora parameter status
String SensorLink::atcmd_status(String at, String _t1_, String _t2_)
{
    char r[10];
    String txt = "";
    Serial2.print(at);
    delay(2000);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isDigit(r[i]))
        {
            if (r[i] == '1')
            {
                txt = _t1_;
            }
            if (r[i] == '0')
            {
                txt = _t2_;
            }
        }
        i++;
    }
    return txt;
}

// Check text return
String SensorLink::atcmd_text(String at)
{
    char r[10];
    String txt = "";
    Serial2.print(at);
    delay(200);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isAlphaNumeric(r[i]))
        {
            txt += r[i];
        }
        i++;
    }
    return txt;
}

// Check int return
String SensorLink::atcmd_int(String at)
{
    char r[10];
    String txt = "";
    Serial2.print(at);
    delay(200);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isDigit(r[i]))
        {
            txt += r[i];
        }
        i++;
    }
    return txt;
}

// Check hex return
String SensorLink::atcmd_hex(String at)
{
    char r[50];
    String txt = "";
    Serial2.print(at);
    delay(200);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isHexadecimalDigital(r[i]) || r[i] == ':')
        {
            txt += r[i];
        }
        i++;
    }
    return txt;
}

// Check payload
String SensorLink::check_payload(String at)
{
    if (at == "A")
    {
        // TOFIX: Acer ship use _GET_REVCN
        Serial2.print(_GET_RECV);
        delay(200);
    }

    char r[2];
    String txt = "";
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if ((isHexadecimalDigit(r[i]) or r[i] == ':') and !isUpperCase(r[i]))
        {
            txt += r[i];
        }
        i++;
    }
    return txt;
}

// set LoRa Parameter
bool SensorLink::atcmd_set(String at, String nvalue)
{
    Serial2.println(at + nvalue);
    delay(1000);
    // Serail2.println("AT+SAVE");
    // delay(1000);
    return true;
}

void SensorLink::wait(int wtime)
{
    for (int i = 0; i < (wtime / 1000); i++)
    {
        Serial.print("###");
        delay(1000);
    }
    Serial.println();
}

/*##########################################
//
//  (1) General commands
//
###########################################*/

// To lora module status
String SensorLink::get_module()
{
    char r[10];
    String txt = "";
    Serial2.print(_GET_AT);
    delay(100);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isAlpha(r[i]))
        {
            txt += r[i];
        }
        i++;
    }
    if (txt == "OK")
    {
        txt = "CONNECTED";
    }
    else
    {
        txt = "DISCONNECT";
    }
    return txt;
}

void SensorLink::set_reboot()
{
    Serial.println("> MODULE REBOOT...");
    Serial2.print("ATZ");
    delay(100);
    Serial.print("> ");
    for (int i = 0; i < 5; i++)
    {
        Serial.print("+++");
        delay(1000);
    }
    Serial.println("\n> REBOOT FINISHED.\n");
}

/*##########################################
//
//  (2) Keys, IDs, EUIs management
//
##########################################*/

// To access the unique application identifier
String SensorLink::get_appeui()
{
    return atcmd_key(_GET_APPEUI);
}
// To access the application key
String SensorLink::get_appkey()
{
    return atcmd_key(_GET_APPKEY);
}

// To set the application session key
String SensorLink::get_appskey()
{
    return atcmd_key(_GET_APPSKEY);
}

// To access the device address
String SensorLink::get_devaddr()
{
    return atcmd_key(_GET_DEVADDR);
}

// To access the unique end-device ID
String SensorLink::get_deveui()
{
    return atcmd_key(_GET_DEVEUI);
}

// To get or set the network session key
String SensorLink::get_nwkskey()
{
    return atcmd_key(_GET_NWKSKEY);
}

/*##########################################
//
//  (3) Joining and sending data
//
##########################################*/

// To access the uplink payload to be confirmed or unconfirmed type
String SensorLink::get_cfm()
{
    return atcmd_status(_GET_CFM, "CONFIRMED", "UNCONFIRMED");
}

// To access the status of the last SEND command
String SensorLink::get_cfs()
{
    return atcmd_status(_GET_CFS, "SUCCESS", "FIALURE");
}

// To join a LoRaWAN network
bool SensorLink::join()
{
    Serial.println("> --------------------------------------");
    Serial.println("> SensorLink LoRa Library. Version V.0.0");
    Serial.println("> LoRaWAN AS918, Lao PDR");
    Serial.println("> --------------------------------------");

    Serial2.print(_GET_AT);
    delay(100);

    return_bool = false;
    while (!return_bool)
    {
        char r[10];
        String njs = "";
        Serial2.print(_GET_NJS);
        delay(1000);
        int i = 0;
        while (Serial2.available())
        {
            r[i] = (char)Serial2.read();
            if (isDigit(r[i]))
            {
                njs = r[i];
            }
            i++;
        }
        if (njs == "1")
        {
            Serial.println(">> NETWORK JOINED");
            return_bool = true;
            break;
        }
        if (njs == "0")
        {
            Serial.print(".");
            Serial2.print(_JOIN);
            delay(8000);
            return_bool = false; // check join again
        }
    }
    return return_bool;
}

// To join a LoRaWAN network in ADP mode
bool SensorLink::join_adp()
{
    Serial2.print(_GET_AT);
    delay(100);
    Serial2.print(_JOIN);
    return_bool = true;

    // TOFIX: Remove if this code's not functioning
    return return_bool;
}

// to access the network join mode
String SensorLink::get_njm()
{
    return atcmd_status(_GET_NJM, "OTAA", "ABP");
}

// To access the current activation status of the device. It shows if the device joined or not in a LoRaWAN network
String SensorLink::get_njs()
{
    return atcmd_status(_GET_NJS, "JOINED", "NOT JOINED");
}

// To access the last received data in hex format
String SensorLink::get_recv()
{
    return atcmd_text(_GET_RECV);
}

// To send data on a dedicated port number
bool SensorLink::send(int p, String t)
{
    String cmd = String(_SEND) + String(p) + String(":") + String(t);
    Serial.println(">> UPLINK: " + String(p) + String(":") + String(t));
    Serial2.print(cmd);
    delay(100);

    char r[10];
    return_bool = false;
    String txt = "";
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isAlpha(r[i]))
        {
            txt += r[i];
        }
        i++;
    }

    if (txt == "OK")
    {
        return_bool = true;
    }

    return return_bool;
}

// To send long packet text data
bool SensorLink::lpsend(int p, int a, String t)
{
    String cmd = String(_LPSEND) + String(p) + String(":") + String(a) + String(":") + String(t);
    Serial.println("<< UPLINK: " + String(p) + String(":") + String(a) + String(":") + String(t));
    Serial2.print(cmd);
    delay(100);

    char r[10];
    return_bool = false;
    String txt = "";
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isAlpha(r[i]))
        {
            txt += r[i];
        }
        i++;
    }

    if (txt == "OK")
    {
        return_bool = true;
    }

    return return_bool;
}

/*##########################################
//
// (4) LoRaWAN command
//
###########################################*/

//  To access the adaptive data rate
String SensorLink::get_adr()
{
    return atcmd_status(_GET_ADR, "ON", "OFF");
}

// To access the LoRaWAN class
String SensorLink::get_loraclass()
{
    char r[10];
    return_text = "";
    Serial2.print(_GET_CLASS);
    delay(100);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isHexadecimalDigit(r[i]))
        {
            if (r[i] == 'A')
            {
                return_text = "A";
            }
            if (r[i] == 'B')
            {
                return_text = "B";
            }
            if (r[i] == 'C')
            {
                return_text = "C";
            }
        }
        i++;
    }
    return return_text;
}

// To access the duty cycle
String SensorLink::get_dcs()
{
    return atcmd_status(_GET_DCS, "ENABLED", "DISABLED");
}

// To access data rate settings
String SensorLink::get_dr()
{
    return atcmd_int(_GET_DR);
}

// To access the join delay info on RX window 1. The range of acceptable values is 1 to 14 seconds
String SensorLink::get_jn1dl()
{
    return atcmd_int(_GET_JN1DL);
}

// To access the join delay info on RX window 2. The range of acceptable values is 2 to 15 seconds.
String SensorLink::get_jn2dl()
{
    return atcmd_int(_GET_JN2DL);
}

// To access the public network mode
String SensorLink::get_pnm()
{
    return atcmd_status(_GET_PNM, "ON", "OFF");
}

// To access the delay of the received window 1. The range of acceptable values is 1 to 15 seconds
String SensorLink::get_rx1dl()
{
    return atcmd_int(_GET_RX1DL);
}

// To access the delay of the received window 2. The range of acceptable values is 2 to 15 seconds
String SensorLink::get_rx2dl()
{
    return atcmd_int(_GET_RX2DL);
}

// To access the data rate of received window 2
String SensorLink::get_rx2dr()
{
    return atcmd_int(_GET_RX2DR);
}

// To access the frequency of the received window 2
String SensorLink::get_rx2fq()
{
    return atcmd_int(_GET_RX2FQ);
}

// To access the transmit power
String SensorLink::get_txp()
{
    char r[10];
    return_text = "";
    Serial2.print(_GET_TXP);
    delay(100);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isDigit(r[i]))
        {
            if (r[i] == '0')
            {
                return_text = "16dBm";
            }
            if (r[i] == '1')
            {
                return_text = "14dBm";
            }
            if (r[i] == '2')
            {
                return_text = "12dBm";
            }
            if (r[i] == '3')
            {
                return_text = "10dBm";
            }
            if (r[i] == '4')
            {
                return_text = "8dBm";
            }
            if (r[i] == '5')
            {
                return_text = "6dBm";
            }
            if (r[i] == '6')
            {
                return_text = "4dBm";
            }
            if (r[i] == '7')
            {
                return_text = "2dBm";
            }
        }
        i++;
    }
    return return_text;
}

// To access the RSSI on reception
String SensorLink::get_rssi()
{
    String txt = atcmd_int(_GET_RSSI);
    String rtext = "-" + txt;
    return rtext;
}

// To get LoRaWAN LBT RSSI
String SensorLink::get_lbtrssi()
{
    return atcmd_int(_GET_LBTRSSI);
}

// To access the SNR of the last received packet
String SensorLink::get_snr()
{
    return atcmd_int(_GET_SNR);
}

// To access the version of the firmware
String SensorLink::get_ver()
{
    char r[10];
    String txt = "";
    Serial2.print(_GET_VER);
    delay(100);
    int i = 0;
    while (Serial2.available())
    {
        r[i] = (char)Serial2.read();
        if (isAlphaNumeric(r[i]) or r[i] == '-')
        {
            txt += r[i];
        }
        i++;
    }
    return txt;
}

/*##########################################
//
//  SET FUNCTION
//
############################################*/

// To set the unique application identifier
bool SensorLink::set_appeui(String _NVALUE_)
{
    return atcmd_set(_SET_APPEUI, _NVALUE_);
}

// To set the application key
bool SensorLink::set_appkey(String _NVALUE_)
{
    return atcmd_set(_SET_APPKEY, _NVALUE_);
}

// To set the application session key
bool SensorLink::set_appskey(String _NVALUE_)
{
    return atcmd_set(_SET_APPSKEY, _NVALUE_);
}

// To set the device address
bool SensorLink::set_devaddr(String _NVALUE_)
{
    return atcmd_set(_SET_DEVADDR, _NVALUE_);
}

// To set the unique end-device ID
bool SensorLink::set_deveui(String _NVALUE_)
{
    return atcmd_set(_SET_DEVEUI, _NVALUE_);
}

// to get or set the network session key.
bool SensorLink::set_nwkskey(String _NVALUE_)
{
    return atcmd_set(_SET_NWKSKEY, _NVALUE_);
}

// To configure the uplink payload to be confirmed or unconfirmed type
bool SensorLink::set_cfm(String _NVALUE_)
{
    return atcmd_set(_SET_CFM, _NVALUE_);
}

// To set the status of the last SEND command
bool SensorLink::set_cfs(String _NVALUE_)
{
    return atcmd_set(_SET_CFS, _NVALUE_);
}

// To access the adaptive data rate
bool SensorLink::set_adr(String _NVALUE_)
{
    return atcmd_set(_SET_ADR, _NVALUE_);
}

// To set the duty cycle
bool SensorLink::set_dcs(String _NVALUE_)
{
    return atcmd_set(_SET_DCS, _NVALUE_);
}

// To set data rate settings
bool SensorLink::set_dr(String _NVALUE_)
{
    return atcmd_set(_SET_DR, _NVALUE_);
}

// to configure the join delay on RX window 1. The range of acceptable values is 1 to 14 seconds
bool SensorLink::set_jn1dl(String _NVALUE_)
{
    return atcmd_set(_SET_JN1DL, _NVALUE_);
}

// to configure the join delay on RX window 2. The range of acceptable values is 2 to 15 seconds.
bool SensorLink::set_jn2dl(String _NVALUE_)
{
    return atcmd_set(_SET_JN2DL, _NVALUE_);
}

// To set the public network mode
bool SensorLink::set_pnm(String _NVALUE_)
{
    return atcmd_set(_SET_PNM, _NVALUE_);
}

// to set the delay of the received window 1. The range of acceptable values is 1 to 15 seconds
bool SensorLink::set_rx1dl(String _NVALUE_)
{
    return atcmd_set(_SET_RX1DL, _NVALUE_);
}

// To set the delay of the received window 2. The range of acceptable values is 2 to 15 seconds
bool SensorLink::set_rx2dl(String _NVALUE_)
{
    return atcmd_set(_SET_RX2DL, _NVALUE_);
}

// To set the frequency of the received window 2
bool SensorLink::set_rx2dr(String _NVALUE_)
{
    return atcmd_set(_SET_RX2DR, _NVALUE_);
}

// To set the frequency of the received window 2
bool SensorLink::set_rx2fq(String _NVALUE_)
{
    return atcmd_set(_SET_RX2FQ, _NVALUE_);
}

// To set the transmit power
bool SensorLink::set_txp(String _NVALUE_)
{
    return atcmd_set(_SET_TXP, _NVALUE_);
}

// to access the LoRaWAN class
bool SensorLink::set_loraclass(String _NVALUE_)
{
    return atcmd_set(_SET_CLASS, _NVALUE_);
}