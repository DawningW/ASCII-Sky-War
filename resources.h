#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <stddef.h>

// �������鳤��
#define length(arr) sizeof(arr) / sizeof(arr[0])

// �洢�ַ���/���Ľṹ��
typedef struct
{
    const char** str;
    int width;
    int height;
} StrObject;
// TODO ͸������

// ��Դö��
typedef enum
{
    // ��ʧ
    MISSINGNO,
    
    // �ַ���
    TITLE,
    GAMEOVER,
    PLANE,
    PLANE2,
    WCNB,
    
    // �ַ���
    WEBSITE,

    MENU,
    BUTTONS,
    DIFFICULTY,
    HELP,
    ABOUT,
    STRINGS,

    // ö��Ԫ������
    COUNT
} Resources;

void res_add(Resources, StrObject*);
StrObject* res_get(Resources);
void res_load();
void res_unload();

#endif // !__RESOURCES_H__
