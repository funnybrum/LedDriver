#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "esp8266-base.h"
#include "LEDDriver.h"
#include "RTC.h"

#define HTTP_PORT 80
#define HOSTNAME "led-driver"

extern Logger logger;
extern Settings settings;
extern WiFiManager wifi;
extern LEDDriver leds;
extern Clock rtc;

