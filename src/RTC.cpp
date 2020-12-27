#include "Main.h"

void Clock::begin() {
    if (!_rtc.begin() || !_rtc.isrunning()) {
        logger.log("RTC failed!");
    } else {
        update();
    }
}

void Clock::loop() {
    // Once each minute read the RTC. This is good enough as we don't care for the seconds.
    // Further optimization can be added if needed by syncing the millis with the RTC and reducing
    // the number of I2C reads.
    if (millis() - _lastRTCRead > 60000) {
        update();
    }
}

void Clock::update() {
    if (!_rtc.isrunning()) {
        logger.log("RTC not running.");
        return;
    }
    _lastRTCRead = millis();
    _now = _rtc.now();
}

uint16_t Clock::getYear() {
    return _now.year();
}

uint8_t Clock::getMonth() {
    return _now.month();
}

uint8_t Clock::getDay() {
    return _now.day();
}

uint8_t Clock::getHour() {
    return _now.hour();
}

uint8_t Clock::getMinute() {
    return _now.minute();
}

void Clock::getConfigPage(char* buffer) {
    sprintf(
        buffer,
        RTC_CONFIG_PAGE,
        getYear(),
        getMonth(),
        getDay(),
        getHour(),
        getMinute());
}
void Clock::parseConfigParams(WebServerBase* webServer) {
    uint16_t year = getYear();
    uint8_t month = getMonth();
    uint8_t day = getDay();
    uint8_t hour = getHour();
    uint8_t minute = getMinute();

    webServer->process_setting("year", year);
    webServer->process_setting("month", month);
    webServer->process_setting("day", day);
    webServer->process_setting("hour", hour);
    webServer->process_setting("minute", minute);

    _now = DateTime(year, month, day, hour, minute, _now.second());
    _rtc.adjust(_now);
}
