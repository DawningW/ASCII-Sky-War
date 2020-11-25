#ifndef __RESOURCES_H__
#define __RESOURCES_H__

// 计算数组长度
#define length(arr) sizeof(arr) / sizeof(arr[0])

// 存储字符串/画的结构体
struct StrObject
{
    const char** str;
    int width;
    int height;
};
// TODO 透明遮罩

// 资源枚举
enum Resources
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
};

void res_add(enum Resources, struct StrObject*);
struct StrObject* res_get(enum Resources);
void res_load();
void res_unload();

#endif // !__RESOURCES_H__
