#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "generated/autoconf.h"

#include "hal_sys_uart.h"
#include "hal_archinfo.h"
#include "hal_crc.h"
#include "hal_gpio.h"
#include "hal_ps2.h"
#include "hal_rcu.h"
#include "hal_rng.h"
#include "hal_rtc.h"
#include "hal_wdg.h"
#include "hal_timer.h"
#include "hal_pwm.h"
#include "hal_qspi.h"
#include "hal_i2c.h"

#include "st7735.h"
#include "pcf8563.h"

void delay_ms(uint32_t val);

#endif