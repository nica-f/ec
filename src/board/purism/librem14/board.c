// SPDX-License-Identifier: GPL-3.0-only

#include <board/battery.h>
#include <board/board.h>
#include <board/gpio.h>
#include <ec/pwm.h>

extern uint8_t main_cycle;

void board_init(void) {
#if 0
    // Allow CPU to boot
//    gpio_set(&SB_KBCRST_N, true);
    // Allow backlight to be turned on
    gpio_set(&BKL_EN, true);
    // Enable camera
    gpio_set(&CCD_EN, true);
    // Enable wireless
    gpio_set(&BT_EN, true);
    gpio_set(&WLAN_EN, true);
    gpio_set(&WLAN_PWR_EN, true);
    // Enable right USB port
    gpio_set(&USB_PWR_EN_N, false);
    // Assert SMI#, SCI#, and SWI#
    gpio_set(&SCI_N, true);
    gpio_set(&SMI_N, true);
    gpio_set(&SWI_N, true);
#endif

    // Turn on CPU fan a bit (further temperature control in peci_event)
    DCR0 = 0x70;
    DCR1 = 0x70;

    // turn off notification LED RGB
    DCR2 = 0xe0; // B
    DCR3 = 0xe0; // G
    DCR4 = 0xe0; // R

    // enable power LED control full brightness
    DCR5 = 0xff;

    // enable keyboard backlight
    DCR6 = 0xff;
}

void board_on_ac(bool ac) {
    /* Fix unused variable */
    ac = ac;
}

void board_event(void) {
}
