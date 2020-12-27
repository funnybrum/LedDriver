#pragma once

#include "user_interface.h"

class LEDDriver {
    public:
        LEDDriver();
        // Channels 0 to 4, duty 0 to 100
        void set(uint8_t channel, uint8_t duty);

    private:
        uint8_t _channelPins[5] = {14, 12, 13, 5, 4};
        uint8_t _funcGpios[5] = {FUNC_GPIO14, FUNC_GPIO12, FUNC_GPIO13, FUNC_GPIO5, FUNC_GPIO4};
};