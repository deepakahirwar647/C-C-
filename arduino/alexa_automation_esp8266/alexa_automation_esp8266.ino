#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include "api_key.h"

// #define WIFI_SSID         "ccccccty"
// #define WIFI_PASS         "12345ghm90"
// #define APP_KEY           "tttttttttttttttt"
// #define APP_SECRET        "ffffffffffffffffffffffff"

// #define RELAY_PIN_1       D1
// #define RELAY_PIN_2       D2
// #define RELAY_PIN_3       D3

// #define SWITCH_ID_1       "hhhhhhhhhhhhhhhhhhhhhhh"
// #define SWITCH_ID_2       "666666666666666666g6666"
// #define SWITCH_ID_3       "jjjjjjjjjjjjjjjjjjjjjjj"

bool onPowerState1(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN_1, state ? LOW : HIGH);
  return true;
}

bool onPowerState2(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN_2, state ? LOW : HIGH);
  return true;
}

bool onPowerState3(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN_3, state ? LOW : HIGH);
  return true;
}

void setupWiFi() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void setupSinricPro() {
  SinricProSwitch &mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);

  SinricProSwitch &mySwitch2 = SinricPro[SWITCH_ID_2];
  mySwitch2.onPowerState(onPowerState2);

  SinricProSwitch &mySwitch3 = SinricPro[SWITCH_ID_3];
  mySwitch3.onPowerState(onPowerState3);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);

  digitalWrite(RELAY_PIN_1, HIGH);
  digitalWrite(RELAY_PIN_2, HIGH);
  digitalWrite(RELAY_PIN_3, HIGH);

  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
