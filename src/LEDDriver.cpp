#include "LEDDriver.h"
#include "Arduino.h"
#include "pwm.h"

// 5 000 000 / 256 = 19.51kHz. Probably will work at 50kHz too, but needs to be confirmed.
#define PWM_PERIOD 256

LEDDriver::LEDDriver() {
    pinMode(this->_channelPins[0], OUTPUT);
    pinMode(this->_channelPins[1], OUTPUT);
    pinMode(this->_channelPins[2], OUTPUT);
    pinMode(this->_channelPins[3], OUTPUT);
    pinMode(this->_channelPins[4], OUTPUT);

    // Refer to https://github.com/StefanBruens/ESP8266_new_pwm for the next few lines.
    uint32 io_info[5][3] = {
        {PERIPHS_IO_MUX_MTDI_U,  this->_funcGpios[0], this->_channelPins[0]},
        {PERIPHS_IO_MUX_MTDI_U,  this->_funcGpios[1], this->_channelPins[1]},
        {PERIPHS_IO_MUX_MTDI_U,  this->_funcGpios[2], this->_channelPins[2]},
        {PERIPHS_IO_MUX_MTDI_U,  this->_funcGpios[3], this->_channelPins[3]},
        {PERIPHS_IO_MUX_MTDI_U,  this->_funcGpios[4], this->_channelPins[4]}
    };
    uint32 pwm_duty_init[5] = {0, 0, 0, 0, 0};
    pwm_init(PWM_PERIOD, pwm_duty_init, 5, io_info);
    pwm_start(); 
}

void LEDDriver::set(uint8_t channel, uint8_t duty) {
    pwm_set_duty(2.56 * duty, channel);
}