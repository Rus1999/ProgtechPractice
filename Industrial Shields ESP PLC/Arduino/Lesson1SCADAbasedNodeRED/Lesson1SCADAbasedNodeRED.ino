/*
   Copyright (c) 2019 Boot&Work Corp., S.L. All rights reserved
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// included library depending of M-Duino version 
#ifdef MDUINO_PLUS
#include <Ethernet2.h>
#else
#include <Ethernet.h>
#endif
// libraries needed for MQTT communication
#include <ArduinoJson.h>
#include <PubSubClient.h>
#define MQTT_ID "demo"
#define NUM_ZONES 1
#define NUM_DIGITAL_OUTPUTS_PER_ZONE 3
#define DIGITAL_OUTPUTS_OFFSET 0
const int digitalOutputs[NUM_ZONES][NUM_DIGITAL_OUTPUTS_PER_ZONE] = {
  {Q0_0, Q0_1, Q0_2},
};
#define NUM_ANALOG_OUTPUTS_PER_ZONE 3
#define ANALOG_OUTPUTS_OFFSET 0
const int analogOutputs[NUM_ZONES][NUM_DIGITAL_OUTPUTS_PER_ZONE] = {
  {A0_5, A0_6, A0_7},
};
#define NUM_DIGITAL_INPUTS_PER_ZONE 7
#define DIGITAL_INPUTS_OFFSET 0
const int digitalInputs[NUM_ZONES][NUM_DIGITAL_INPUTS_PER_ZONE] = {
  {I0_0, I0_1, I0_2, I0_3, I0_4, I0_5, I0_6},
};
#define NUM_ANALOG_INPUTS_PER_ZONE 6
#define ANALOG_INPUTS_OFFSET 7
#define ANALOG_INPUTS_THRESHOLD 5 // Filtering threshold
const int analogInputs[NUM_ZONES][NUM_ANALOG_INPUTS_PER_ZONE] = {
  {I0_7, I0_8, I0_9, I0_10, I0_11, I0_12},
};

byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xAE };
IPAddress broker(10, 10, 10, 60);
/* Set an IP address for the MQTT-Broker. Remember to set the same static IP address in the device
set as a broker.*/
IPAddress ip(10, 10, 10, 70); //SET HERE THE IP ADDRESS FOR YOUR M-DUINO 
unsigned port = 1883;
// Initialize client
EthernetClient client;
PubSubClient mqtt(client);
int digitalInputsValues[NUM_ZONES][NUM_DIGITAL_INPUTS_PER_ZONE];
int analogInputsValues[NUM_ZONES][NUM_ANALOG_INPUTS_PER_ZONE];
////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){ 
  Ethernet.begin(mac, ip);
  mqtt.setServer(broker, port);
  mqtt.setCallback(receiveMqttMessage);
  // Init variables
  for (int i = 0; i < NUM_ZONES; ++i) {
    for (int j = 0; j < NUM_DIGITAL_INPUTS_PER_ZONE; ++j) {
      digitalInputsValues[i][j] = digitalRead(digitalInputs[i][j]);
    }
    for (int j = 0; j < NUM_ANALOG_INPUTS_PER_ZONE; ++j) {
      analogInputsValues[i][j] = analogRead(analogInputs[i][j]);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  if (!mqtt.connected()) {
    reconnect();
  } else {
    // maintain connection with server
    mqtt.loop();
  }
  // update the real value of the inputs
  updateInputs();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void updateInputs() {
  for (int i = 0; i < NUM_ZONES; ++i) {
    for (int j = 0; j < NUM_DIGITAL_INPUTS_PER_ZONE; ++j) {
      updateDigitalInput(i, j);
    }
    for (int j = 0; j < NUM_ANALOG_INPUTS_PER_ZONE; ++j) {
      updateAnalogInput(i, j);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void updateDigitalInput(int zone, int index) {
  int value = digitalRead(digitalInputs[zone][index]);
  if (value != digitalInputsValues[zone][index]) {
    digitalInputsValues[zone][index] = value;
    publishInput(zone, index + DIGITAL_INPUTS_OFFSET, value);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void updateAnalogInput(int zone, int index) {
  int value = analogRead(analogInputs[zone][index]);
  int minValue = value > ANALOG_INPUTS_THRESHOLD ? value - ANALOG_INPUTS_THRESHOLD : 0;
  int maxValue = value < 1023 - ANALOG_INPUTS_THRESHOLD ? value + ANALOG_INPUTS_THRESHOLD : 1023;
  if ((analogInputsValues[zone][index] < minValue) || (analogInputsValues[zone][index] > maxValue)) {
    analogInputsValues[zone][index] = value;
    publishInput(zone, index + ANALOG_INPUTS_OFFSET, value);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void setDigitalOutput(char *payload, unsigned int len) {
  DynamicJsonBuffer json(JSON_OBJECT_SIZE(3));
  JsonObject &root = json.parseObject(payload, len);
  if (root.success()) {
    int zone = root["zone"];
    if (zone >= NUM_ZONES) {
      // Invalid zone
      return;
    }
    int index = root["index"];
    index -= DIGITAL_OUTPUTS_OFFSET;
    if (index >= NUM_DIGITAL_OUTPUTS_PER_ZONE) {
      // Invalid digital output
      return;
    }
    int value = root["value"];
    digitalWrite(digitalOutputs[zone][index], value);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void setAnalogOutput(char *payload, unsigned int len) {
  DynamicJsonBuffer json(JSON_OBJECT_SIZE(3));
  JsonObject &root = json.parseObject(payload, len);
  if (root.success()) {
    int zone = root["zone"];
    if (zone >= NUM_ZONES) {
      // Invalid zone
      return;
    }
    int index = root["index"];
    index -= ANALOG_OUTPUTS_OFFSET; 
    if (index >= NUM_ANALOG_OUTPUTS_PER_ZONE) {
      // Invalid analog output
      return;
    }
    int value = root["value"];
    analogWrite(analogOutputs[zone][index], value);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void reconnect() {
  if (mqtt.connect(MQTT_ID)) {
    mqtt.subscribe("Q");
    mqtt.subscribe("A");
  } else {
    // MQTT connect fail
    client.stop();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void receiveMqttMessage(char* topic, byte* payload, unsigned int len) {
  if (strcmp(topic, "Q") == 0) {
    // Set digital output
    setDigitalOutput((char*) payload, len);
  } else if (strcmp(topic, "A") == 0) {
    // Set analog output
    setAnalogOutput((char*) payload, len);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void publishInput(int zone, int index, int value) {
  DynamicJsonBuffer json(JSON_OBJECT_SIZE(3));
  JsonObject &root = json.createObject();
  if (root.success()) {
    root["zone"] = zone;
    root["index"] = index;
    root["value"] = value;
    publish("I", root);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void publish(const char *topic, JsonObject &root) {
  unsigned len = root.measureLength();
  if (len > 0) {
    char *payload = new char[len + 1];
    if (payload) {
      root.printTo(payload, len + 1);
      publish(topic, payload);
      delete[] payload;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void publish(const char *topic, const char *payload) {
  if (mqtt.connected()) {
    mqtt.publish(topic, payload);
  }
}