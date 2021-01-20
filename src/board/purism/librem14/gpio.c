// SPDX-License-Identifier: GPL-3.0-only

#include <board/gpio.h>
#include <common/debug.h>


#if 0
GPA0	GPIO	PWM	FAN_PWMIN		fan 0 pwm speed
GPA1	GPIO	PWM	FAN_PWMIN1		fan 1 pwm speed
GPA2	GPIO	PWM	OSNOTIFY_LED_BLUE	notification LED blue, pwm brightness
GPA3	GPIO	PWM	OSNOTIFY_LED_GREEN	notification LED green, pwm brightness
GPA4	GPIO	PWM	PSNOTIFY_LED_RED	notification LED red, pwm brightness
GPA5	GPIO	PWM	PWR_LED_PWM		power/charging LEDs brightness
GPA6	GPIO	OUT	KB_LT			keybaord backlight
GPA7	GPIO	OUT	V1.05A_PWRGD

GPB0	GPIO	IN	PM_SLP_S0#
GPB1	GPIO	OUT	CAPSLOCK_LED_WHITE	capslock LED (in keyboard) on/off
GPB2	X
GPB3	I2C	SMCLK	SMB_CLK_BT		battery controller (in battery pack)
GPB4	I2C	SMDAT	SMB_DATA_BT		battery controller (in battery pack)
GPB5	GPIO	OUT	ALL_SYS_PWRGD_VRON
GPB6	GPIO	IN	EC_PCH_RCIN#
GPB7	GPIO	OUT	PM_RSMRST#

GPC0	GPIO	OUT	POWER_TP_ON
GPC1	I2C	SMCLK	I2C_CLK1
GPC2	I2C	SMDAT	I2C_DATA1
GPC3	GPIO	OUT	PM_SLP_SUS#
GPC4	GPIO	OUT	AC_PRESENT
GPC5	GPIO	OUT	PWR_LED_WHITE		pwr/charging white LED enable
GPC6	GPIO	OUT	LAN_VDDEN		GBit LAN port power supply enable/disable
GPC7	GPIO	OUT	BT_ON			W_DISABLE2 on WiFi/BT M.2 slot

GPD0	GPIO	OUT	Wifi_poweron		WiFi/BT M.2 power supply on/off
GPD1	GPIO	IN	DDR3VR_PWRGD
GPD2	GPIO	IN	PLT_RST_BUF#
GPD3	GPIO	OUT	SMC_RUNTIME_SCI#
GPD4	X
GPD5	GPIO	OUT	WIRELESS_ON		W_DISABLE1 on WiFi/BT M.2 slot
GPD6	GPIO	IN	KBC_FAN_SPEED		fan 0 tacho input
GPD7	GPIO	IN	KBC_FAN_SPEED1		fan 1 tacho input

GPE0	GPIO	IN	LED_ON			LCD LED backlight enable
GPE1	GPIO	OUT	SMC_SHUTDOWN#
GPE2	GPIO	IN	+V0.95A_PWRGD
GPE3	GPIO	OUT	EC_MUTE#		mute audio DAC?
GPE4	GPIO	IN	SMC_ONOFF#
GPE5	GPIO	IN	ROP_SYS_PWROK
GPE6	GPIO	IN	PM_SUS_STAT#
GPE7	GPIO	OUT	PM_BATLOW#

GPF0	GPIO	OUT	MIC_SEL_SPDIF		audio codec SPDIF0/GPIO2 -> toggle for headphone mic input?
GPF1	GPIO	OUT	+V0.95A_EN
GPF2	GPIO	IN	ROP_VCCST_PWRGD
GPF3	GPIO	OUT	WIFI_LED_WHITE		WiFi/BT HKS white LED
GPF4	GPIO	OUT	ME_FLASH
GPF5	GPIO	IN	A_POWER_OK
GPF6	GPIO	IN	H_PECI_EC
GPF7	NC

GPG0		IN	SPI Enable ?
GPG1	GPIO	IN	PCH_PWROK
GPG2		IN	SPI Enable ?
GPG3	FSCE#
GPG4	FMOSI
GPG5	FMISO
GPG6	GPIO	OUT	+V1.05A_EN
GPG7	FSCK

GPH0	LPC		LPC_CLKRUN#
GPH1	I2C		I2C_CLK3			BQ24715 battery charge controller
GPH2	I2C		I2C_DATA3			BQ24715 battery charge controller
GPH3	GPIO	OUT	BLCTL				LCD LED backlight control ?
GPH4	GPIO	OUT	PM_EC_PWRBTN#			
GPH5	GPIO	IN	TYPE_EC_IRQ
GPH6	GPIO	IN	MAIN_LID			LCD lid open/close switch

GPI0	GPIO	IN	Chager_IOUT			BQ24715 IOUT
GPI1	GPIO	IN	BAT_VDEK			+VBAT detect
GPI2	GPIO	IN	BAT-DEK#			battery pack detect?
GPI3	GPIO	IN	PM_SLP_S4#
GPI4	GPIO	IN	PM_SLP_S3#
GPI5	GPIO	IN	ADP_IN#				DC adapter (charger) present
GPI6	GPIO	IN	EARPHONE_DET			3.5mm jack headphone detect
GPI7	GPIO	OUT	TYPEC_P2_PWREN			type-C USB port 5V power enable

GPJ0	GPIO	IN	PROCHOT#_EC
GPJ1	GPIO	OUT	DIS_BAT				
GPJ2	GPIO	OUT	CAM_ON				power on camera
GPJ3	GPIO	IN	DCOVER_DET			NA
GPJ4	GPIO	OUT	CHG_LED_ORANGE			power/chargeing LED orange enable/disable
GPJ5	GPIO	OUT	CHG_LED_GREEN			power/chargeing LED green enable/disable

GPM0	LPC	INOUT	LPC_AD0
GPM1	LPC	INOUT	LPC_AD1
GPM2	LPC	INOUT	LPC_AD2
GPM3	LPC	INOUT	LPC_AD3
GPM4	LPC	IN	EC_LPC_CLK
GPM5	LPC	OUT	LPC_FRAME#
GPM6	LPC	INOUT	INT_SERIRQ

KSO0 - KSO15 / KSI0 - KSI7  keyboard matrix
#endif

struct Gpio __code ACIN_N =         GPIO(B, 6);
struct Gpio __code AC_PRESENT =     GPIO(E, 7);
struct Gpio __code ALL_SYS_PWRGD =  GPIO(C, 0);
struct Gpio __code BKL_EN =         GPIO(H, 2);
struct Gpio __code BT_EN =          GPIO(F, 3);
struct Gpio __code BUF_PLT_RST_N =  GPIO(D, 2);
struct Gpio __code CCD_EN =         GPIO(G, 0);
struct Gpio __code DD_ON =          GPIO(E, 4);
struct Gpio __code EC_EN =          GPIO(E, 1);
struct Gpio __code EC_RSMRST_N =    GPIO(E, 5);
struct Gpio __code LAN_WAKEUP_N =   GPIO(B, 2);
struct Gpio __code LED_ACIN =       GPIO(C, 7);
struct Gpio __code LED_AIRPLANE_N = GPIO(G, 6);
struct Gpio __code LED_BAT_CHG =    GPIO(A, 5);
struct Gpio __code LED_BAT_FULL =   GPIO(A, 6);
struct Gpio __code LED_PWR =        GPIO(A, 7);
struct Gpio __code LID_SW_N =       GPIO(D, 1);
struct Gpio __code PCH_DPWROK_EC =  GPIO(A, 3);
struct Gpio __code PCH_PWROK_EC =   GPIO(A, 4);
struct Gpio __code PM_CLKRUN_N =    GPIO(H, 0);
struct Gpio __code PM_PWROK =       GPIO(C, 6);
struct Gpio __code PWR_BTN_N =      GPIO(D, 5);
struct Gpio __code PWR_SW_N =       GPIO(D, 0);
struct Gpio __code SB_KBCRST_N =    GPIO(E, 6);
struct Gpio __code SCI_N =          GPIO(D, 4);
struct Gpio __code SLP_SUS_N =      GPIO(I, 2);
struct Gpio __code SMI_N =          GPIO(D, 3);
struct Gpio __code SUSB_N_PCH =     GPIO(H, 6);
struct Gpio __code SUSC_N_PCH =     GPIO(H, 1);
struct Gpio __code SUSWARN_N =      GPIO(D, 7);
struct Gpio __code SUS_PWR_ACK =    GPIO(J, 0);
struct Gpio __code SWI_N =          GPIO(E, 0);
struct Gpio __code USB_PWR_EN_N =   GPIO(F, 7);
struct Gpio __code VA_EC_EN =       GPIO(E, 3);
struct Gpio __code VR_ON =          GPIO(H, 4);
struct Gpio __code WLAN_EN =        GPIO(H, 5);
struct Gpio __code WLAN_PWR_EN =    GPIO(J, 4);

void gpio_init() {
    // Enable LPC reset on GPD2
    GCR = 0x04;

    // Set GPIO data
    GPDRA = 0;
    // NC
    GPDRB = (1 << 0);
    GPDRC = 0;
    // PWR_BTN#, SCI#, SMI#
    GPDRD = (1 << 5) | (1 << 4) | (1 << 3);
    GPDRE = 0;
    // USB_PWR_EN#, H_PECI
    GPDRF = 0xC0; // (1 << 7) | (1 << 6)
    // AIRPLAIN_LED#
    GPDRG = (1 << 6);
    GPDRH = 0;
    GPDRI = 0;
    GPDRJ = 0;

    // Set GPIO control
    // EC_SSD_LED#
    GPCRA0 = GPIO_IN;
    // KBC_BEEP
    GPCRA1 = GPIO_ALT;
    // CPU_FAN
    GPCRA2 = GPIO_ALT;
    // PCH_DPWROK_EC
    GPCRA3 = GPIO_IN;
    // PCH_PWROK_EC
    GPCRA4 = GPIO_OUT;
    // LED_BAT_CHG
    GPCRA5 = GPIO_OUT;
    // LED_BAT_FULL
    GPCRA6 = GPIO_OUT;
    // LED_PWR
    GPCRA7 = GPIO_OUT;
    // NC
    GPCRB0 = GPIO_OUT;
    // H_PROCHOT_EC
    GPCRB1 = GPIO_OUT;
    // LAN_WAKEUP#
    GPCRB2 = GPIO_IN | GPIO_UP;
    // SMC_BAT
    GPCRB3 = GPIO_ALT;
    // SMD_BAT
    GPCRB4 = GPIO_ALT;
    // GA20
    GPCRB5 = GPIO_OUT;
    // AC_IN#
    GPCRB6 = GPIO_IN | GPIO_UP;
    // FP_RST#
    GPCRB7 = GPIO_IN;
    // ALL_SYS_PWRGD
    GPCRC0 = GPIO_IN;
    // SMC_VGA_THERM
    GPCRC1 = GPIO_ALT;
    // SMD_VGA_THERM
    GPCRC2 = GPIO_ALT;
    // KSO16 (Darter)
    GPCRC3 = GPIO_IN;
    // CNVI_DET#
    GPCRC4 = GPIO_OUT;
    // KSO17 (Darter)
    GPCRC5 = GPIO_IN;
    // PM_PWROK
    GPCRC6 = GPIO_OUT;
    // LED_ACIN
    GPCRC7 = GPIO_OUT;
    // PWR_SW#
    GPCRD0 = GPIO_IN | GPIO_UP;
    // LID_SW#
    GPCRD1 = GPIO_IN | GPIO_UP;
    // BUF_PLT_RST#
    GPCRD2 = GPIO_ALT;
    // SMI#
    GPCRD3 = GPIO_IN;
    // SCI#
    GPCRD4 = GPIO_IN;
    // PWR_BTN#
    GPCRD5 = GPIO_OUT;
    // CPU_FANSEN
    GPCRD6 = GPIO_ALT;
    // SUSWARN#
    GPCRD7 = GPIO_IN;
    // SWI#
    GPCRE0 = GPIO_OUT;
    // EC_EN
    GPCRE1 = GPIO_OUT;
    // PCH_SLP_WLAN#_R
    GPCRE2 = GPIO_IN;
    // VA_EC_EN
    GPCRE3 = GPIO_OUT;
    // DD_ON
    GPCRE4 = GPIO_OUT;
    // EC_RSMRST#
    GPCRE5 = GPIO_OUT;
    // SB_KBCRST#
    GPCRE6 = GPIO_OUT;
    // AC_PRESENT / PM_PWROK
    GPCRE7 = GPIO_OUT;
    // 80CLK
    GPCRF0 = GPIO_IN;
    // USB_CHARGE_EN
    GPCRF1 = GPIO_OUT;
    // 3IN1
    GPCRF2 = GPIO_IN | GPIO_UP;
    // BT_EN
    GPCRF3 = GPIO_OUT;
    // TP_CLK
    GPCRF4 = GPIO_ALT;
    // TP_DATA
    GPCRF5 = GPIO_ALT;
    // H_PECI
    GPCRF6 = GPIO_ALT;
    // USB_PWR_EN#
    GPCRF7 = GPIO_OUT;
    // CCD_EN
    GPCRG0 = GPIO_OUT;
    // 3G_EN
    GPCRG1 = GPIO_OUT;
    // VDD3
    GPCRG2 = GPIO_OUT;
    // HSPI_CE#
    GPCRG3 = GPIO_ALT;
    // HSPI_MSI
    GPCRG4 = GPIO_ALT;
    // HSPI_MSO
    GPCRG5 = GPIO_ALT;
    // AIRPLAN_LED#
    GPCRG6 = GPIO_OUT;
    // HCPI_SCLK
    GPCRG7 = GPIO_ALT;
    // EC_CLKRUN#
    GPCRH0 = GPIO_ALT;
    // SUSC#_PCH
    GPCRH1 = GPIO_IN;
    // BKL_EN
    GPCRH2 = GPIO_OUT;
    // NC
    GPCRH3 = GPIO_OUT;
    // VR_ON
    GPCRH4 = GPIO_IN;
    // WLAN_EN
    GPCRH5 = GPIO_OUT;
    // SUSB#_PCH
    GPCRH6 = GPIO_IN;
    // Unknown
    GPCRH7 = GPIO_IN;
    // BAT_DET
    GPCRI0 = GPIO_ALT;
    // BAT_VOLT
    GPCRI1 = GPIO_ALT;
    // SLP_SUS#
    GPCRI2 = GPIO_IN;
    // THERM_VOLT
    GPCRI3 = GPIO_ALT;
    // TOTAL_CUR
    GPCRI4 = GPIO_ALT;
    // AZ_RST#_EC
    GPCRI5 = GPIO_IN;
    // LIGHT_KB_DET#
    GPCRI6 = GPIO_IN;
    // MODEL_ID
    GPCRI7 = GPIO_IN;
    // SUS_PWR_ACK
    GPCRJ0 = GPIO_IN | GPIO_DOWN;
    // KBC_MUTE#
    GPCRJ1 = GPIO_IN;
    // ME_WE
    GPCRJ2 = GPIO_OUT;
    // SOC_TYPE
    GPCRJ3 = GPIO_IN;
    // WLAN_PWR_EN
    GPCRJ4 = GPIO_OUT;
    // KBLIGHT_ADJ
    GPCRJ5 = GPIO_ALT;
    // 3G_PWR_EN
    GPCRJ6 = GPIO_OUT;
    // NC
    GPCRJ7 = GPIO_IN;
    // LPC_AD0
    GPCRM0 = GPIO_ALT;
    // LPC_AD1
    GPCRM1 = GPIO_ALT;
    // LPC_AD2
    GPCRM2 = GPIO_ALT;
    // LPC_AD3
    GPCRM3 = GPIO_ALT;
    // PCLK_KBC
    GPCRM4 = GPIO_ALT;
    // LPC_FRAME#
    GPCRM5 = GPIO_ALT;
    // SERIRQ
    GPCRM6 = GPIO_ALT;
}

#if GPIO_DEBUG
void gpio_debug_bank(
    char * bank,
    uint8_t data,
    uint8_t mirror,
    uint8_t pot,
    volatile uint8_t * control
) {
    for(char i = 0; i < 8; i++) {
        DEBUG(
            "%s%d:\n\tdata %d\n\tmirror %d\n\tpot %d\n\tcontrol %02X\n",
            bank,
            i,
            (data >> i) & 1,
            (mirror >> i) & 1,
            (pot >> i) & 1,
            *(control + i)
        );
    }
}

void gpio_debug(void) {
    #define bank(BANK) gpio_debug_bank(#BANK, GPDR ## BANK, GPDMR ## BANK, GPOT ## BANK, &GPCR ## BANK ## 0)
    bank(A);
    bank(B);
    bank(C);
    bank(D);
    bank(E);
    bank(F);
    bank(G);
    bank(H);
    bank(I);
    bank(J);
    #undef bank
}
#endif
