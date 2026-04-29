#ifndef __SHELL_PORT_H__
#define __SHELL_PORT_H__

#include "libgcc.h"
#include "stdio.h"
#include "hal_hp_uart.h"
#include "stdint.h"
#include "string.h"
#include "ff.h"

extern uint32_t envInt;
extern uint16_t envShort;
extern char envString[128];
extern char envChar;
extern uint32_t envFunc;

void create_shell_env_varible();

// #define USE_FATFS


short shellRead(char* str, unsigned short len);

short shellWrite(char* str, unsigned short len);

size_t getcwd(char* dir, size_t dirLen);

size_t chdir(char * dir);

// 将dir的内容输出到buffer中
size_t listdir(char *dir, char *buffer, size_t maxLen);

size_t createfile(char *dir, char *filename);

#endif
