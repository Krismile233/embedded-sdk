#include <stddef.h>
#include <stdint.h>

// 简单的 memcpy 实现
void *memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    
    while (n--) {
        *d++ = *s++;
    }
    
    return dest;
}

// 简单的 memset 实现
void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    
    while (n--) {
        *p++ = (unsigned char)c;
    }
    
    return s;
}

// 简单的 strlen 实现
size_t strlen(const char *s) {
    size_t len = 0;
    while (*s++) {
        len++;
    }
    return len;
}

size_t memcmp(const void* ptr1, const void* ptr2, size_t num) {
    const unsigned char* p1 = (const unsigned char*)ptr1;
    const unsigned char* p2 = (const unsigned char*)ptr2;
    
    while (num--) {
        if (*p1 != *p2) {
            return (*p1 - *p2);
        }
        p1++;
        p2++;
    }
    
    return 0;
}

char* strchr(const char* str, int c) {
    // 标准 strchr 将 c 转换为 char
    char target = (char)c;
    
    // 循环，包括最后的 '\0'
    do {
        if (*str == target) {
            return (char*)str;  // 返回匹配位置的指针
        }
    } while (*str++ != '\0');
    
    return NULL;
}