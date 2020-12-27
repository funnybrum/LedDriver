#include "LEDDriver.h"
#include "Arduino.h"
#include "pwm.h"

// 5 000 000 / 256 = 19.51kHz. Probably will work at 50kHz too, but needs to be confirmed.

// GPIO output pins are 14, 12, 13, 5, 4

LEDDriver::LEDDriver() {
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);

    // Refer to https://github.com/StefanBruens/ESP8266_new_pwm for the next few lines.
    uint32 io_info[5][3] = {
        {PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4, 4},
        {PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5, 5},
        {PERIPHS_IO_MUX_MTDI_U,  FUNC_GPIO12, 12},
        {PERIPHS_IO_MUX_MTCK_U,  FUNC_GPIO13, 13},
        {PERIPHS_IO_MUX_MTMS_U,  FUNC_GPIO14, 14}
    };
    uint32 pwm_duty_init[5] = {0, 0, 0, 0, 0};
    pwm_init(256, pwm_duty_init, 5, io_info);
}

void LEDDriver::set(uint8_t channel, uint8_t duty) {
    pwm_set_duty(2.56 * duty, channel);
    pwm_start();
}
