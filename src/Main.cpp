#include "Main.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
SystemCheck systemCheck = SystemCheck(&logger);
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);
LEDDriver leds = LEDDriver();

void setup()
{ 
    Serial.begin(74880);
    while (! Serial) {
        delay(1);
    }
    settings.begin();
    wifi.begin();
    webServer.begin();

    wifi.connect();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    delay(100);
}
