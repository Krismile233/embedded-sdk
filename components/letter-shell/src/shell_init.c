#include "shell_init.h"

// 如果发现系统不正常重启，大概率是执行了地址为0的函数（可能因为函数未定义）

void load_shell(){
    char shellBuffer[1024];
    char shellPathBuffer[1024] = "/";

#ifdef USE_FATFS
    ShellFs shellfs;
    Shell shell;

    printf("Hello World From SysUart.\r\n");
    hal_hp_uart_putstr("\r\n");


    hal_hp_uart_putstr("Waiting for filesystem booting...\r\n");

    load_filesystem();

    hal_hp_uart_putstr("Waiting for shell_fs booting...\r\n");  
    shellfs.chdir = chdir;
    shellfs.getcwd = getcwd;
    shellfs.listdir = listdir;
    shellfs.createfile = createfile;
    shellFsInit(&shellfs, shellPathBuffer, 1024);

    hal_hp_uart_putstr("Waiting for shell booting...\r\n");
    shell.read = shellRead;
    shell.write = shellWrite;
    shellSetPath(&shell,shellPathBuffer);
    shellInit(&shell, shellBuffer, 1024);
    shellCompanionAdd(&shell, SHELL_COMPANION_ID_FS, &shellfs);
#else
    Shell shell;

    printf("Hello World From SysUart.\r\n");
    hal_hp_uart_putstr("\r\n");
    hal_hp_uart_putstr("Waiting for shell booting...\r\n");
    shell.read = shellRead;
    shell.write = shellWrite;
    shellSetPath(&shell,shellPathBuffer);
    shellInit(&shell, shellBuffer, 1024);
#endif

    while(1){
        shellTask(&shell);
    }
}