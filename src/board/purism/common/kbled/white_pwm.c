// SPDX-License-Identifier: GPL-3.0-only

#include <board/kbled.h>
#include <ec/pwm.h>

void kbled_init(void) {
    //TODO: enable PWMs
    kbled_reset();
}

void kbled_reset(void) {
    // Set brightness and color
    kbled_set_color(0xFFFFFF);
    kbled_set(0x00);
}

uint8_t kbled_get(void) {
    // Get PWM for power
    return DCR6;
}

uint8_t kbled_max(void) {
    return 255;
}

void kbled_set(uint8_t level) {
    // Set PWM for power
    DCR6 = level;
}

uint32_t kbled_get_color(void) {
    return 0xffffff;
}

void kbled_set_color(uint32_t color) {
    color = color;
    return;
}
