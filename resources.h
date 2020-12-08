#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <stddef.h>

// 计算数组长度
#define length(arr) sizeof(arr) / sizeof(arr[0])

// 存储字符串/画的结构体
typedef struct
{
    const char** str;
    int width;
    int height;
} StrObject;
// TODO 透明遮罩

// 资源枚举
typedef enum
{
    // 丢失
    MISSINGNO,
    
    // 字符画
    TITLE,
    GAMEOVER,
    PLANE,
    PLANE2,
    WCNB,
    
    // 字符串
    WEBSITE,

    MENU,
    BUTTONS,
    DIFFICULTY,
    HELP,
    ABOUT,
    STRINGS,

    // 枚举元素数量
    COUNT
} Resources;

void res_add(Resources, StrObject*);
StrObject* res_get(Resources);
void res_load();
void res_unload();

#endif // !__RESOURCES_H__
