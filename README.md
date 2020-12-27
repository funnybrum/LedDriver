# Led Driver

5 channel LED PWM driver with integrated RTC that can choose what pattern should be used based on the current time. An example use-case would be LED driver for kitche LED strip with the following configuration:
 * Night time - 2700K, 30% duty cycle
 * Early morning - 4000K 60% duty cycle
 * Day time - 4500K 100% duty cycle
 * Evening - 3000K 80% duty cycle

The PWM frequency will be as high as possible (probably ~10Khz) to reduce flickering. The PCB (with some minor issues like the missing SDA/SCL pull up resistors) can be found [here](https://easyeda.com/funnybrum/wifi-led-driver).

## Building the project

The project uses a common set of tools that are availabe in another repo - https://github.com/funnybrum/esp8266-base. Clone the esp8266-base repo in the lib folder:

```
cd lib
git clone git@github.com:funnybrum/esp8266-base.git
```

## Notes
1) Uses https://github.com/StefanBruens/ESP8266_new_pwm for PWM. The pwm.c in the src folder is direct copy.
2) The RTClib.cpp has been modified to work with SDA/SCL on pins 0 and 2.