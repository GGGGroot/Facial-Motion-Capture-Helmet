
#include "headfile.h"


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
            .brightness = 100,
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


void lightUpMultipleLEDs(const std::vector<int>& ledIndices,uint32_t color) {
	if (ws2811_init(&ledstring) != WS2811_SUCCESS) {
		std::cerr << "ws2811_init failed" << std::endl;
	}

	for (int ledIndex : ledIndices) {
		if (ledIndex >= 0 && ledIndex < LED_COUNT) {
			ledstring.channel[0].leds[ledIndex] = color;
		}
		else {
			std::cerr << "Invalid LED index: " << ledIndex << std::endl;
		}
	}

	// 渲染LED颜色
	if (ws2811_render(&ledstring) != WS2811_SUCCESS) {
		std::cerr << "ws2811_render failed" << std::endl;
	}



	ws2811_fini(&ledstring);
}
