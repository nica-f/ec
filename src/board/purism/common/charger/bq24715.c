// SPDX-License-Identifier: GPL-3.0-only
//
// TI BQ24715 Smart Charger
// https://www.ti.com/lit/ds/symlink/bq24780s.pdf

#include <board/battery.h>
#include <board/smbus.h>
#include <common/debug.h>

// ChargeOption0 flags
// Low Power Mode Enable
#define SBC_EN_LWPWR        ((uint16_t)(1 << 15))
// Watchdog Timer Adjust
#define SBC_WDTMR_ADJ_175S  ((uint16_t)(0b11 << 13))
// Switching Frequency
#define SBC_PWM_FREQ_800KHZ ((uint16_t)(0b01 << 8))
// AudioFrequencyLimit
#define SBC_AUDIO_FREQ_LIM  ((uint16_t)(1 << 10))
// ChargeInhibit
#define SBC_CHARGE_INHIBIT  ((uint16_t)(1 << 0))

// XXX: Assumption: ac_last is initialized high.
static bool charger_enabled = false;

int battery_charger_disable(void) {
    int res = 0;

    if (!charger_enabled) return 0;

    DEBUG("CHG disable\n");

    // Set charge option 0 with 175s watchdog
    res = smbus_write(
        CHARGER_ADDRESS,
        0x12,
        /* SBC_EN_LWPWR |*/
        SBC_WDTMR_ADJ_175S |
        SBC_PWM_FREQ_800KHZ |
        SBC_AUDIO_FREQ_LIM |
        SBC_CHARGE_INHIBIT
    );

    // Disable charge current
    res = smbus_write(CHARGER_ADDRESS, 0x14, 0);
    if (res < 0) return res;

    // Disable charge voltage
    res = smbus_write(CHARGER_ADDRESS, 0x15, 0);
    if (res < 0) return res;

    // Disable input current
    res = smbus_write(CHARGER_ADDRESS, 0x3F, 0);
    if (res < 0) return res;

    DEBUG("Charger disabled\n");
    charger_enabled = false;
    return 0;
}

int battery_charger_enable(void) {
    int res = 0;

    if (charger_enabled) return 0;

    DEBUG("CHG enable @ %dmV %dmA\n", battery_charge_voltage, battery_charge_current);

    res = battery_charger_disable();
    if (res < 0) return res;

    // Set charge current in mA
    //res = smbus_write(CHARGER_ADDRESS, 0x14, CHARGER_CHARGE_CURRENT);
    res = smbus_write(CHARGER_ADDRESS, 0x14, battery_charge_current);
    if (res < 0) return res;

    // Set charge voltage in mV
    // res = smbus_write(CHARGER_ADDRESS, 0x15, CHARGER_CHARGE_VOLTAGE);
    res = smbus_write(CHARGER_ADDRESS, 0x15, battery_charge_voltage);
    if (res < 0) return res;

    // Set input current in mA
    res = smbus_write(CHARGER_ADDRESS, 0x3F, CHARGER_INPUT_CURRENT);
    if (res < 0) return res;

    // Set charge option 0 with watchdog disabled
    res = smbus_write(
        CHARGER_ADDRESS,
        0x12,
        SBC_EN_LWPWR |
        SBC_PWM_FREQ_800KHZ |
        SBC_AUDIO_FREQ_LIM /*|
        SBC_CHARGE_INHIBIT*/ // XXX for testing disabled
    );

    DEBUG("Charger enabled\n");
    charger_enabled = true;
    return 0;
}

void battery_charger_event(void) {
    //TODO: watchdog
    DEBUG("CHG event\n");
}

void battery_debug(void) {
    uint16_t data = 0;
    int res = 0;

    #define command(N, A, V) { \
        DEBUG("  " #N ": "); \
        res = smbus_read(A, V, &data); \
        if (res < 0) { \
            DEBUG("ERROR %04X\n", -res); \
        } else { \
            DEBUG("%04X\n", data); \
        } \
    }

    DEBUG("Charger (bq24715):\n");
    command(ChargeOption0, CHARGER_ADDRESS, 0x12);
    command(ChargeCurrent, CHARGER_ADDRESS, 0x14);
    command(ChargeVoltage, CHARGER_ADDRESS, 0x15);
    command(MinSysVoltage, CHARGER_ADDRESS, 0x3E);
    command(InputCurrent, CHARGER_ADDRESS, 0x3F);
    command(ManufacturerID, CHARGER_ADDRESS, 0xFE);
    command(DeviceID, CHARGER_ADDRESS, 0xFF);

    #undef command
}
