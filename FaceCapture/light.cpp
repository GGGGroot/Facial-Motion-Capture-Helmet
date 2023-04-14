#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "ws2811.h"

#define LED_COUNT 4 // 根据实际LED数量调整
#define GPIO_PIN 18
#define DMA_CHANNEL 10

ws2811_t ledstring = {
    .freq = WS2811_TARGET_FREQ,
    .dmanum = DMA_CHANNEL,
    .channel = {
        [0] = {
            .gpionum = GPIO_PIN,
            .invert = 0,
            .count = LED_COUNT,
            .strip_type = WS2811_STRIP_GRB,
            .leds=0,
            .brightness = 255,
            .wshift=0,
            .rshift=0,
            .gshift=0,
            .bshift=0,
            .gamma=0,
        },
        [1] = {
            .gpionum = 0,
            .invert = 0,
            .count = 0,
            .strip_type = WS2811_STRIP_GRB,
            .leds=0,
            .brightness = 0,
            .wshift=0,
            .rshift=0,
            .gshift=0,
            .bshift=0,
            .gamma=0,
        },
    },
};

void handleSignal(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        ws2811_fini(&ledstring);
        exit(0);
    }
}

void chase(uint32_t color, int wait) {
    for (int j = 0; j < LED_COUNT + 1; j++) {
        for (int i = 0; i < LED_COUNT; i++) {
            if (i == j - 1) {
                ledstring.channel[0].leds[i] = color;
            } else {
                ledstring.channel[0].leds[i] = 0x000000;
            }
        }
        ws2811_render(&ledstring);
        usleep(wait * 1000);
    }
}
void lightup(uint32_t color) {
    if (ws2811_init(&ledstring) != WS2811_SUCCESS) {
        std::cerr << "ws2811_init failed" << std::endl;
        return 1;
    }

    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    //uint32_t color = 0x00FF00; // 绿色
    int wait = 1000; // 100毫秒的延迟
    chase(color, wait);

    for (int i = 0; i < LED_COUNT; i++) {
        ledstring.channel[0].leds[i] = 0x000000;
    }

    if (ws2811_render(&ledstring) != WS2811_SUCCESS) {
        std::cerr << "ws2811_render failed" << std::endl;
        return 1;
    }

    ws2811_fini(&ledstring);

}
