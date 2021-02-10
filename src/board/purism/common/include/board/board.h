// SPDX-License-Identifier: GPL-3.0-only

#ifndef _BOARD_BOARD_H
#define _BOARD_BOARD_H

#include <stdbool.h>

void board_init(void);
void board_event(void);
void board_on_ac(bool ac);

void board_battery_init(void);
bool board_battery_detect(void);
uint16_t board_battery_get_voltage(void);
uint16_t board_get_battery_charge(void);

#endif // _BOARD_BOARD_H
