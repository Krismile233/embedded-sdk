#ifndef __MAIN_H__
#define __MAIN_H__

// System Headers
#include "string.h"
#include "stdio.h"
#include "libgcc.h"
#include "stdint.h"
#include "stdbool.h"

// System Configuration
#include "generated/autoconf.h"
#include "board.h"

// Components headers
#include "hal_timer.h"
#include "hal_qspi.h"
#include "hal_gpio.h"
#include "hal_pwm.h"
#include "hal_hp_uart.h"
#include "hal_i2c.h"
#include "hal_sys_uart.h"

// Device headers
#include "st7735.h"
#include "sgp30.h"

void delay_ms(uint32_t ms);

#define PSRAM_SCKL_FREQ_MHZ (CONFIG_CPU_FREQ_MHZ / CONFIG_PSRAM_NUM)
#endif