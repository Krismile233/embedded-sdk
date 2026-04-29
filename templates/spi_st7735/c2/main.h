#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "generated/autoconf.h"
#include "libgcc.h"

#include "hal_sys_uart.h"
#include "hal_gpio.h"
#include "hal_qspi.h"
#include "hal_timer.h"
#include "hal_pwm.h"
#include "hal_hp_uart.h"
#include "hal_i2c.h"

#include "st7735.h"
#include "sgp30.h"

void delay_ms(uint32_t ms);

#endif