# SPDX-License-Identifier: GPL-3.0-only

EC=it8528e

# Add keymap to src
KEYMAP?=default
SRC+=$(BOARD_DIR)/keymap/$(KEYMAP).c

# Set keyboard LED mechanism
KBLED=white_pwm

# Set charger I2C bus
CFLAGS+=-DI2C_SMBUS=I2C_3

# Set battery I2C bus
CFLAGS+=-DI2C_BATTERY=I2C_0

# Set I2C bus for debug output
CFLAGS+=-DI2C_DEBUGBUS=I2C_0

# Set smart charger parameters
CFLAGS+=\
	-DCHARGER_CHARGE_CURRENT=1536 \
	-DCHARGER_CHARGE_VOLTAGE=17600 \
	-DCHARGER_INPUT_CURRENT=3200

# Set battery charging thresholds
CFLAGS+=\
	-DBATTERY_START_THRESHOLD=0 \
	-DBATTERY_END_THRESHOLD=100

# Add Purism common code
include src/board/purism/common/common.mk
