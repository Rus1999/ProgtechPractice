/*
 * Modified simple esp32 Gmail send example
 */

#include "Arduino.h"
#include <EMailSender.h>

#define SENDER_EMAIL "account_login@gmail.com"
#define SENDER_PASSWORD "<YOUR-GMAIL-PASSWD>"
#define RECEIVER_EMAIL "receive_email@gmail.com"
//#define USE_ETH

EMailSender emailSend(SENDER_EMAIL, SENDER_PASSWORD);

#ifndef USE_ETH
#include <WiFi.h>
const char* ssid = "<YOUR-SSID>";
const char* password = "<YOUR-PASSWD>";
uint8_t connection_state = 0;
uint16_t reconnect_interval = 10000;

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr) {
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);
        Serial.println(nSSID);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50) {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits() {
    uint32_t ts = millis();
    while(!connection_state) {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state) {
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}
#endif

void setup() {
    Serial.begin(115200);

#ifdef USE_ETH
    uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
    Ethernet.begin(mac);
#else
    connection_state = WiFiConnect(ssid, password);
    if(!connection_state)  // if not connected to WIFI
        Awaits();          // constantly trying to connect
#endif

    EMailSender::EMailMessage message;
    message.subject = "Hello";
    message.message = "Come to www.industrialshields.com";

    EMailSender::Response resp = emailSend.send(RECEIVER_EMAIL, message);

    Serial.println("Sending status: ");

    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
}

void loop() {}