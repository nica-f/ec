// SPDX-License-Identifier: GPL-3.0-only

#include <stdbool.h>
#include <arch/delay.h>
#include <board/battery.h>
#include <board/board.h>
#include <board/gpio.h>
//#include <common/i2c.h>
#include <ec/adc.h>
#include <ec/i2c.h>
#include <common/debug.h>


//
// true if a battery is present, false otherwise
//
bool board_battery_detect(void)
{
    if (gpio_get(&BAT_DETECT))
        return false;
    else
        return true;
}

static uint16_t last_voltage_read = 0;

//
// returns battery charge in % (0-100)
// based on last battery readings
//
uint16_t board_get_battery_charge(void)
{
uint16_t tvol;
uint16_t bchgst;
static unsigned char ravg=0; // rolling average
static unsigned char ravg2=0;
static unsigned char ravg3=0;

    if (battery_design_voltage == 0)
        return 0;
    tvol=last_voltage_read;
    tvol -= battery_min_voltage; // lower threshold, = 0%
    bchgst = ((30000 / (battery_design_voltage-battery_min_voltage)) * tvol) / 300;

    if (bchgst > 100)
        bchgst = 100;

    ravg = (ravg + ravg2 + ravg3 + bchgst) / 4;
    ravg3 = ravg2;
    ravg2 = ravg;

    battery_remaining_capacity = (battery_design_capacity / 100) * ravg;

    return ravg; // in % from 0 to 100 - hopefully
}

//
// reads current battery voltage in mV
// in Librem 14 from EC ADC channel 1
//
uint16_t board_battery_get_voltage(void)
{
uint8_t to=0;
uint16_t adcval;
uint16_t tvol;

    // we may have to wait for ADC to finish
    while (to++ < 100 && !(VCH0CTL & (1L << 7)))
        delay_us(100);

    if (!(VCH0CTL & (1L << 7)))
        DEBUG("BAT !adc sts=0x%02x ctl=0x%02x\n", ADCSTS, VCH0CTL);

    adcval = (((uint16_t)VCH0DATM & 0x03) << 8) | VCH0DATL;
    // max bat voltage at max ADC value = 15.4V
    tvol = ((14000000 / 0x3ff) * adcval) / 1000;

    // clear ADC to start new cycle
    VCH0CTL |= (1L << 7);

    last_voltage_read = tvol;

    battery_charge = board_get_battery_charge();

    return tvol;
}

#define BAT_EEPROM_ADR (0xa0 >> 1)

static bool read_eeprom(void)
{
int res;
uint8_t vendor_id;
uint8_t cell_brand_id;
uint8_t battery_pack_S;
uint8_t battery_pack_T;
uint16_t charge_voltage;
uint16_t charge_current;
uint16_t design_capacity;
uint16_t design_voltage;
uint16_t max_discharge_current;

    // first read is a probe, if this fails there is no EEPROM
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x00, &vendor_id, 1);
    if (res < 0) {
        DEBUG("bat eep r=%d\n", res);
        return false;
    }
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x01, &cell_brand_id, 1);
    if (res < 0)
        cell_brand_id=0;
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x02, &battery_pack_S, 1);
    if (res < 0)
        battery_pack_S=0;
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x03, &battery_pack_T, 1);
    if (res < 0)
        battery_pack_T=0;
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x04, &charge_voltage, 2);
    if (res < 0)
        charge_voltage=0;
    else
        battery_charge_voltage=charge_voltage;
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x06, &design_capacity, 2);
    if (res < 0)
        design_capacity=0;
    else {
        battery_design_capacity = design_capacity;
        battery_full_capacity = design_capacity; // we can not determine anything else
    }
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x08, &design_voltage, 2);
    if (res < 0)
        design_voltage=0;
    else
        battery_design_voltage = design_voltage;
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x0A, &max_discharge_current, 2);
    if (res < 0)
        max_discharge_current=0;
    res = i2c_get(&I2C_0, BAT_EEPROM_ADR, 0x0C, &charge_current, 2);
    if (res < 0)
        charge_current=0;
    else
        battery_charge_current=charge_current;

    DEBUG("  VID:      0x%02x\n", vendor_id);
    DEBUG("  cell ID:  0x%02x\n", cell_brand_id);
    DEBUG("  pack-S:   0x%02x\n", battery_pack_S);
    DEBUG("  pack-T:   0x%02x\n", battery_pack_T);
    DEBUG("  chg-volt: %dmV\n", charge_voltage);
    DEBUG("  chg-cur:  %dmA\n", charge_current);
    DEBUG("  des-cap:  %d\n", design_capacity);
    DEBUG("  des-volt: %dmV\n", design_voltage);
    DEBUG("  dis-cur:  %dmA\n", max_discharge_current);

    battery_temp = 20; // no thermistor, assume 20C ?
    battery_min_voltage = 9600;

    battery_current = 0; // we have no means to tell the current/rate

    return true;
}

#define BAT_GAS_GAUGE_ADDR (0x16 >> 1)

static bool probe_gas_gauge(void)
{
int res;
unsigned char tval;

    res = i2c_get(&I2C_0, BAT_GAS_GAUGE_ADDR, 0x00, &tval, 1);
    if (res < 0) {
        DEBUG("bat gauge r=%d\n", res);
        return false;
    } else
        return true;
}

// try to figure out which battery we have
void board_battery_init(void)
{
    battery_voltage = 0;
    battery_temp = 0;
    battery_current = 0;
    battery_charge = 0;
    battery_remaining_capacity = 0;
    battery_full_capacity = 0;
    battery_design_capacity = 0;
    battery_design_voltage = 0;
    battery_status &= ~BATTERY_INITIALIZED;

    battery_present = board_battery_detect();

    if (battery_present) {
        battery_voltage = board_battery_get_voltage();
        if (read_eeprom()) {
            DEBUG("I: 3-cell bat found\n");
            battery_status |= BATTERY_INITIALIZED;
        } else {
            if (probe_gas_gauge()) {
                battery_temp = 0;
                battery_current = 0;
                battery_charge = 0;
                battery_remaining_capacity = 0;
                battery_full_capacity = 8800;
                battery_design_capacity = 8800;
                battery_design_voltage = 7600;
                battery_charge_current = 1760;
                battery_charge_voltage = 8700;
                battery_min_voltage = 6000;
            } else {
                DEBUG("E: unknown bat, keeping charger off!\n");
                battery_status &= ~BATTERY_INITIALIZED;
            }
        }
    }
}
