#include "main.h"

void main(){
    create_shell_env_varible();

    hal_sys_uart_init();
    hal_hp_uart_init(115200);

    load_shell();

    while(1){
        printf("Never Reaching here.\r\n");
    }
    
}
