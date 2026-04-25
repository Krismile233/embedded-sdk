#include "init.h"

FATFS fs_Flash;   //FatFs文件系统对象
FRESULT res_Flash;//文件操作结果
uint8_t work_buf[4096] __attribute__((aligned(4))); // 按扇区对齐的缓冲区，用于文件系统初始化

bool load_filesystem(){
    MKFS_PARM opt = {
        .fmt = FM_FAT,
        .n_fat = 2, // 主区域+备份区域
        .align = 0, // 对齐读写
        .n_root = 0, // （默认）设置根目录占1个扇区大小
        .au_size = 4096, // 设置簇大小=扇区大小
        
    };

    bool isMount = false;

    for(uint8_t i = 0; i<=3; i++){
        if(i==3){
            printf("Exceed the maximum number of retries, exit :(");
        }

        printf("Mounting FileSystem...\n");
        res_Flash = f_mount(&fs_Flash,"0:",1);
        if(res_Flash == FR_NO_FILESYSTEM){
            printf("Do not find a FileSystem...\n");
            printf("Make a new FileSystem...\n");
            res_Flash = f_mkfs("0:", &opt, work_buf, sizeof(work_buf));
            if(res_Flash == FR_MKFS_ABORTED){
                printf("Fail in making a new FileSystem, abort.\n");
                isMount = false;
                break;
            }else{
                printf("Make a new FileSystem success, go ahead.\n");
                continue;
            }
        }else{
            isMount = true;
            printf("Mount FileSystem success!\n");
            break;
        }
    }
    
    return isMount;
}