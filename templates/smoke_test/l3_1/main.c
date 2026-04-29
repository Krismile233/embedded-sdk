#include "main.h"

void delay_ms(uint32_t val) {
    hal_delay_ms(0, val);
}

void archinfo_test(void){
    printf("=============================================\n");
    printf("             archinfo test                   \n");
    printf("=============================================\n");
    hal_archinfo_info();
    printf("write regs\n");
    hal_archinfo_set_sys(0x4004);
    hal_archinfo_set_idl(0x5F3E);
    hal_archinfo_set_idh(0x6E2);
    hal_archinfo_info();
    printf("=============================================\n\n");
}

void crc_test(void){
    printf("==============================================\n");
    printf("                crc test                      \n");
    printf("==============================================\n");
    hal_crc_set_ctrl(0);
    hal_crc_set_init(0xFFFF);
    hal_crc_set_xorv(0);
    hal_crc_set_ctrl(0b1001001);
    uint32_t val = 0x123456;
    for(int i = 0; i < 10; ++i) {
        hal_crc_set_data(val + i);
        printf("i: %d CRC: %x\n", i, hal_crc_get_val());
    }
    printf("==============================================\n\n");
}

void gpio_led_test(void){
    printf("==============================================\n");
    printf("              gpio led test                   \n");
    printf("==============================================\n");

    gpio_hal_output_enable(NULL, 26);
    gpio_hal_output_enable(NULL, 27);

    for(int i = 0; i<3; i++){
        gpio_hal_set_level(NULL, 26, 1);
        gpio_hal_set_level(NULL, 27, 1);
        delay_ms(500);
        gpio_hal_set_level(NULL, 26, 0);
        gpio_hal_set_level(NULL, 27, 0);
        delay_ms(500);
    }
    printf("==============================================\n\n");
}

void i2c_pcf8563_test(void){
    printf("==============================================\n");
    printf("            i2c pcf8563b test                 \n");
    printf("==============================================\n");

    hal_i2c_config_t i2c_cfg = { .pscr = 99 };
    hal_i2c_init(HAL_I2C_PORT_0, &i2c_cfg);

    pcf8563_device_t rtc_dev = {
        .i2c_port = HAL_I2C_PORT_0,
        .i2c_addr = 0x51
    };
    pcf8563_init(&rtc_dev);

    pcf8563_info_t init1_info = {
        .time.second = 00,
        .time.minute = 33,
        .time.hour = 14,
        .date.weekday = 4,
        .date.day = 15,
        .date.month = 5,
        .date.year = 25
    };
    pcf8563_write_info(&rtc_dev, &init1_info);
    printf("Write 2025-05-15 14:33:00 done\n");

    printf("read from PCF8563B\n");
    pcf8563_info_t rd_info = {0};
    for (int i = 0; i < 3; ++i) {
        rd_info = pcf8563_read_info(&rtc_dev);
        printf("[PCF8563B] 20%02d-%02d-%02d w:%d %02d:%02d:%02d\n",
            rd_info.date.year,
            rd_info.date.month,
            rd_info.date.day,
            rd_info.date.weekday,
            rd_info.time.hour,
            rd_info.time.minute,
            rd_info.time.second);
        delay_ms(1000);
    }
    printf("==============================================\n\n");
}

void ps2_test(void){
    printf("==============================================\n");
    printf("              ps2 test                        \n");
    printf("==============================================\n");
    printf("ESC to exit\n");

    hal_ps2_set_ctrl(0b11);
    uint32_t kdb_code, i = 0;
    while (1) {
        kdb_code = hal_ps2_get_data();
        if (kdb_code != 0) {
            printf("[%d] dat: %x\n", i++, kdb_code);
        }
        if (kdb_code == 0x76) {
            break;
        }
    }
    printf("==============================================\n\n");
}

void pwm_led_test(void){
    printf("==============================================\n");
    printf("              pwm led test                    \n");
    printf("==============================================\n");

    pwm_config_t pwm_cfg = { .pscr = 100, .cmp = 1000 };
    pwm_hal_init(NULL, 0, &pwm_cfg);

    uint32_t cnt = 2;
    while(cnt--){
        for (uint32_t duty = 0; duty <= 1000; duty += 100) {
            pwm_hal_set_compare(NULL, 0, 0, duty);
            pwm_hal_set_compare(NULL, 0, 1, duty);
            pwm_hal_enable(NULL, 0);
            delay_ms(20);
        }
        for (uint32_t duty = 1000; duty >= 100; duty -= 100) {
            pwm_hal_set_compare(NULL, 0, 0, duty);
            pwm_hal_set_compare(NULL, 0, 1, duty);
            pwm_hal_enable(NULL, 0);
            delay_ms(20);
        }
    }
    printf("==============================================\n\n");
}

void rcu_test(void){
    printf("==============================================\n");
    printf("              rcu test                        \n");
    printf("==============================================\n");
    hal_rcu_set_ctrl(0b1011);
    hal_rcu_set_rdiv(255);
    printf("STAT: %d\n", hal_rcu_get_stat());
    printf("==============================================\n\n");
}

void rng_test(void){
    printf("==============================================\n");
    printf("              rng test                        \n");
    printf("==============================================\n");
    hal_rng_set_ctrl(1);
    hal_rng_set_seed(0xFE1C);
    for(int i = 0; i < 5; ++i) {
        printf("[normal]random val: %x\n", hal_rng_get_val());
    }
    printf("reset seed\n");
    hal_rng_set_seed(0);
    for(int i = 0; i < 3; ++i) {
        printf("[reset] val: %x\n", hal_rng_get_val());
    }
    printf("==============================================\n\n");
}

void rtc_test(void){
    printf("==============================================\n");
    printf("              rtc test                        \n");
    printf("==============================================\n");
    hal_rtc_set_ctrl(1);
    hal_rtc_set_prescale(48);

    for(uint32_t i = 0; i < 3; ++i) {
        hal_rtc_set_cnt(123 * i);
        hal_rtc_set_alrm(hal_rtc_get_cnt() + 10);
        printf("[static]CNT: %d\n", hal_rtc_get_cnt());
    }
    hal_rtc_set_cnt(0);
    hal_rtc_set_ctrl(0b0010010);

    printf("cnt inc test\n");
    for(int i = 0; i < 3; ++i) {
        while(hal_rtc_get_ista() != 1);
        printf("RTC_REG_CNT: %d\n", hal_rtc_get_cnt());
    }
    printf("cnt inc test done\n");
    printf("==============================================\n\n");
}

void timer_test(void){
    printf("==============================================\n");
    printf("              timer test                      \n");
    printf("==============================================\n");
    hal_sys_tick_init(0);

    printf("no div test start\n");
    for (int i = 1; i <= 3; ++i) {
        hal_delay_ms(0, 1000);
        printf("delay 1s\n");
    }
    printf("no div test done\n");
    printf("==============================================\n\n");
}

void wdg_test(void){
    printf("==============================================\n");
    printf("              wdg test                        \n");
    printf("==============================================\n");
    hal_wdg_set_key(0x5F3759DF);
    hal_wdg_set_ctrl(0x0);

    hal_wdg_set_key(0x5F3759DF);
    hal_wdg_set_prescale(99);

    hal_wdg_set_key(0x5F3759DF);
    hal_wdg_set_cmp(499);

    hal_wdg_set_key(0x5F3759DF);
    hal_wdg_set_ctrl(0b101);

    hal_wdg_set_key(0x5F3759DF);
    hal_wdg_feed(0x1);

    hal_wdg_set_key(0x5F3759DF);
    hal_wdg_feed(0x0);

    for(int i = 0; i < 3; ++i){
        while(hal_wdg_get_stat() == 0);
        printf("%d wdg reset trigger\n", i);
    }
    printf("==============================================\n\n");
}

st7735_device_t tft_dev = {
    .dc_gpio_port = 1,
    .dc_gpio_pin = 6,
    .qspi_port = HAL_QSPI_PORT_0,
    .qspi_cs = 0,
    .screen_width = 128,
    .screen_height = 128,
    .rotation = 3,
    .horizontal_offset = 2,
    .vertical_offset = 3
};

void spi_tft_init(void) {
    printf("GPIO INIT DONE\n");

    hal_qspi_config_t qspi_config = { .clkdiv = 4 };
    hal_qspi_init(HAL_QSPI_PORT_0, &qspi_config);

    printf("tft init begin\n");
    st7735_init(&tft_dev);
}

void st7735_test(void){
    printf("==============================================\n");
    printf("            st7735 lcd test                   \n");
    printf("==============================================\n");
    spi_tft_init();
    printf("==============================================\n\n");
}

int main(void) {
    hal_sys_uart_init();
    printf("StarrySkyL3_1 Smoke Test Start\n");
    hal_sys_tick_init(0);

    archinfo_test();
    crc_test();
    gpio_led_test();
    pwm_led_test();
    rcu_test();
    rng_test();
    rtc_test();
    timer_test();
    i2c_pcf8563_test();
    st7735_test();

    printf("NOTE: skipping PS2 test by default\n");
    printf("NOTE: skipping WDG test by default\n");

    printf("All test done\n");
    while(1);
    return 0;
}