#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "ws2811.h"

ws2811_t ledstring();
void handleSignal(int signal);
void chase(uint32_t color, int wait);
void lightup(uint32_t color);
