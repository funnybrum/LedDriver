#pragma once

#include "user_interface.h"

class LEDDriver {
    public:
        LEDDriver();
        // Channels 0 to 4, duty 0 to 100
        void set(uint8_t channel, uint8_t duty);
};