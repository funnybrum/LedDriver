#include "Main.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/set", std::bind(&WebServer::handle_set, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    wifi.parse_config_params(this);
    rtc.parseConfigParams(this);

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);

    char rtc_settings[strlen_P(RTC_CONFIG_PAGE) + 32];
    rtc.update();
    rtc.getConfigPage(rtc_settings);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings,
        rtc_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_set() {
    if (server->hasArg("channel") && server->hasArg("duty")) {
    uint8_t channel = server->arg("channel").toInt();
    uint8_t duty = server->arg("duty").toInt();
        if (channel <= 4 && duty <= 100) {
            logger->log("Channel %d to %d%%", channel, duty);
            leds.set(channel, duty);
            server->send(200);
            return;
        }
    }

    server->send(404, "text/plain", "Missing or incorrect channel/duty parameters. Try with /set?channel=2&duty=50.");
}
